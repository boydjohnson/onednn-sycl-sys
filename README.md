# onednn-sycl-sys

[![Build Status](https://github.com/boydjohnson/onednn-sycl-sys/actions/workflows/ci-intel.yml/badge.svg)](https://github.com/boydjohnson/onednn-sycl-sys/actions/workflows/ci-intel.yml)

`onednn-sycl-sys` provides low-level Rust bindings to a C api to a very small part of the SYCL Buffer (sycl/buffer.hpp) API. This is necessary for passing a SYCL Buffer in the [high-level oneDNN Rust bindings](http://github.com/boydjohnson/onednnl-rs).


## Usage

This crate provides `unsafe` bindings, so you'll need to use `unsafe` blocks;
