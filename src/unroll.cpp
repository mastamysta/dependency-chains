#include <iostream>
#include <cstdint>
#include <array>

// The idea here is to iterate a list, summing the values

#define LIST_SIZE 10000
#define LIST_TYPE int
using lt = std::array<LIST_TYPE, LIST_SIZE>; 

template <typename T, std::size_t S>
class gen
{
public:
    constexpr auto operator()() -> lt
    {
        std::array<T, S> ret = { 0};

        for (int i = 0; i < S; i++)
            ret[i] = i;

        return ret;
    }
};

static auto rolled(const lt& data)
{
    LIST_TYPE sum = 0;

    for (int i = 0; i < LIST_SIZE; i++)
        sum += data[i];

    return sum;
}

static auto unrolled(const lt& data)
{
    LIST_TYPE sum0 = 0, sum1 = 0, sum2 = 0, sum3 = 0;

    for (int i = 0; i < LIST_SIZE; i+=4)
    {
        sum0 += data[i];
        sum1 += data[i+1];
        sum2 += data[i+2];
        sum3 += data[i+3];
    }

    return sum0 + sum1 + sum2 + sum3;
}

template <std::size_t... Is>
static auto complete_unroll(const lt& data, std::index_sequence<Is...> inds)
{
    int a = 0;

    a += (data[Is] + ... );

    return a;
}

template <std::size_t STEP, std::size_t... Is>
static auto helper(const lt& data, std::index_sequence<Is...> inds)
{
    int a = 0, b = 0, c = 0, d = 0;

    a += (data[STEP * Is] + ... );
    b += (data[STEP * Is + 1] + ... );
    c += (data[STEP * Is + 2] + ... );
    d += (data[STEP * Is + 3] + ... );

    return a + b + c + d;
}

template <std::size_t SIZE, std::size_t STEP>
static auto complete_unroll_macc(const lt& data)
{
    constexpr std::size_t ind_seq_siz = SIZE / STEP;

    return helper<STEP>(data, std::make_index_sequence<ind_seq_siz>());
}

int main()
{
    gen<LIST_TYPE, LIST_SIZE> g;
    constexpr auto data = g();

    int ret;

    for (int i = 0; i < 100000; i++)
    {
#ifdef UNROLL
        ret = unrolled(data);
#else
    #ifdef COMP_UNROLL
        ret = complete_unroll(data, std::make_index_sequence<LIST_SIZE>());
    #else
        #ifdef COMP_MUNROLL
            ret = complete_unroll_macc<LIST_SIZE, 4>(data);
        #else
            ret = rolled(data);
        #endif
    #endif
#endif
    }

//    std::cout << ret << "\n";

    return 0;
}
