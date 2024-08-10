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

int main()
{
    gen<LIST_TYPE, LIST_SIZE> g;
    constexpr auto data = g();

    for (int i = 0; i < 100000; i++)
    {
#ifdef UNROLL
        unrolled(data);
#else
    #ifdef COMP_UNROLL
        complete_unroll(data, std::make_index_sequence<LIST_SIZE>());
    #else
        rolled(data);
    #endif
#endif
    }

    return 0;
}
