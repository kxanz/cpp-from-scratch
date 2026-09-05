#pragma once




namespace kxanz 
{
    template <typename T>
    struct custom_deleter
    {
        void operator()(T* pointer) const
        {
            delete pointer;
        }
    };

    template <typename T, typename custom_deleter = custom_deleter<T>>
    class unique_ptr
    {
    public:
        unique_ptr() 
        { 
        }
        unique_ptr(T* pointer)
        {
        }

        unique_ptr(const unique_ptr&) { };
        unique_ptr& operator=(const unique_ptr&) { };

        unique_ptr(unique_ptr&& other) noexcept
        {

        }

        unique_ptr& operator=(unique_ptr&& other) noexcept
        {

        }

        ~unique_ptr()
        {

        }

        T* release()
        {

        }

        void reset(T* pointer)
        {

        }

        bool is_owning() const { }


        T& operator*() const { }
        T* operator->() const { }
        operator bool() const { }

    private:
    };
}
