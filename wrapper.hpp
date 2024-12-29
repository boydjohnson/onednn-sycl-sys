#include "sycl/sycl.hpp"
#include <iostream>

extern "C"
{

    void *sycl_dnn_buffer_create_with_host_data(void *host_data, size_t size_in_bytes)
    {
        try
        {

            auto buf = new sycl::buffer<char, 1>(static_cast<char *>(host_data), sycl::range(size_in_bytes), {sycl::property::buffer::use_host_ptr()});

            return static_cast<void *>(buf);
        }
        catch (const sycl::exception &e)
        {
            // Handle exceptions (e.g., log the error)
            std::cerr << "SYCL Exception: " << e.what() << std::endl;
            return nullptr;
        }
    }

    // Destroy the SYCL buffer
    void sycl_dnn_buffer_destroy(void *buffer_ptr)
    {
        try
        {
            auto buf = static_cast<sycl::buffer<char> *>(buffer_ptr);
            delete buf;
        }
        catch (const sycl::exception &e)
        {
            // Handle exceptions (e.g., log the error)
        }
    }
}
