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
            std::cerr << "SYCL Exception: " << e.what() << std::endl;
            return nullptr;
        }
    }

    void sycl_dnn_buffer_destroy(void *buffer_ptr)
    {
        try
        {
            auto buf = static_cast<sycl::buffer<char> *>(buffer_ptr);
            delete buf;
        }
        catch (const sycl::exception &e)
        {
            std::cerr << "SYCL Exception: " << e.what() << std::endl;
        }
    }

    void sycl_dnn_buffer_write_to_host_data(void *buffer_ptr, void *host_data, size_t size_in_bytes)
    {
        try
        {
            if (!buffer_ptr || !host_data)
            {
                std::cerr << "Error: Invalid buffer pointer or host data pointer." << std::endl;
                return;
            }

            sycl::buffer<char, 1> *buf = static_cast<sycl::buffer<char, 1> *>(buffer_ptr);

            sycl::host_accessor host_acc(*buf, sycl::write_only);

            std::memcpy(host_data, host_acc.get_pointer(), size_in_bytes);
        }
        catch (const sycl::exception &e)
        {
            std::cerr << "SYCL Exception: " << e.what() << std::endl;
        }
    }
}
