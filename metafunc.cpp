#include <iostream>
#include <bitset>
#include <array>
#include <string>
#include <vector>
#include <list>

template <typename T>
struct is_vector_or_list : std::true_type
{
};

template <typename T>
struct is_vector_or_list<std::vector<T>> : std::true_type
{
};

template <typename T>
struct is_vector_or_list<std::list<T>> : std::true_type
{
};

template <typename T>
/*inline*/ constexpr bool is_vector_or_list_v = is_vector_or_list<T>::value;

template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, void>::type
ip_filter(const T &_ip)
{
  std::string res{};

  if (_ip < 0)
  {
    res += "255";
  }
  else
  {
    std::string str = std::bitset<8 * sizeof(T)>(_ip).to_string();

    while (!str.empty())
    {
      res += std::to_string(std::bitset<8>(str).to_ulong());
      res += ".";
      str.erase(0, 8);
    }

    // удаляем последний символ точки
    res.pop_back();
  }

  std::cout << res << std::endl;
}

template <typename T>
inline typename std::enable_if<std::is_same<T, std::string>::value, void>::type
ip_filter(const T &_ip)
{
  std::cout << _ip << std::endl;
}

template <typename T, typename = std::enable_if_t<is_vector_or_list_v<T>>>
void ip_filter(T &_ip)
{
  std::string res{};

  for (auto it = _ip.cbegin(); it != _ip.cend(); it++)
  {
    res += std::to_string(*it);
    res += ".";
  }
  // удаляем последний символ точки
  res.pop_back();

  std::cout << res << std::endl;
}

int main()
{
  ip_filter(int8_t{-1});
  ip_filter(int16_t{0});
  ip_filter(int32_t{2130706433});
  ip_filter(int64_t{8875824491850138409});
  ip_filter(std::string{"Hello, World !"});

  std::vector<int> ip_vector{100, 200, 300, 400};
  std::list<short> ip_list{400, 300, 200, 100};

  ip_filter(ip_vector);
  ip_filter(ip_list);

  return 0;
}