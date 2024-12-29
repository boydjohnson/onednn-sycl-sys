use std::{env, path::PathBuf};

fn main() {
    let bindings = bindgen::Builder::default()
        .header("wrapper.hpp")
        .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
        .allowlist_function("sycl_dnn_.*")
        .opaque_type("std::.*")
        .opaque_type("sycl::.*")
        .layout_tests(false)
        .generate_comments(true)
        .clang_arg("-fretain-comments-from-system-headers")
        .clang_arg("-I/opt/intel/oneapi/compiler/latest/include")
        .clang_arg("-I/opt/intel/oneapi/compiler/latest/include/sycl")
        .generate()
        .unwrap();

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");

    println!("cargo:rustc-link-lib=sycl");

    cc::Build::new()
        .cpp(true)
        .std("c++17")
        .file("wrapper.cpp")
        .static_flag(true)
        .compiler("/opt/intel/oneapi/compiler/latest/bin/icpx")
        .include("/opt/intel/oneapi/compiler/latest/include")
        .include("/opt/intel/oneapi/compiler/latest/include/sycl")
        .flag("-fsycl")
        .compile("sycl_wrapper");

    println!("cargo:rustc-link-lib=static=sycl_wrapper");
}
