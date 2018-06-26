
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 26.06.18.
//

#ifndef BIZARRETALE_SINGLETON_HPP
#define BIZARRETALE_SINGLETON_HPP
template <typename T>
class Singleton
{
protected:
    Singleton() noexcept = default;
    Singleton(Singleton const&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton &operator=(Singleton const&) = delete;
    Singleton &operator=(Singleton&&) = delete;
    virtual ~Singleton() = default;
public:
    static T &Instance()
    {
        static T *t = new T();
        return *t;
    }
};

#endif //BIZARRETALE_SINGLETON_HPP
