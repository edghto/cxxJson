# cxxJson
Simple library for serializing/deserializing json from/to regular c++ structure.

Highly inspired by piece of code written by my colleague in one of latests project.
Main purpose of this was to have fun with c++ template metaprogramming. 

## Limitations
* supports only boost::property_tree::ptree as json parser
* array can contain only elements of the same type

## Example
```cxx

namespace TestTypes {

struct FooObject
{
    int i;
    bool b;
    std::string str;

    bool operator ==(const FooObject& that)
    {
        return i == that.i
                && b == that.b
                && str == that.str;
    }
};

} // namespace TestTypes

BOOST_FUSION_ADAPT_STRUCT(
    TestTypes::FooObject,
    (int, i)
    (bool, b)
    (std::string, str)
);

int main()
{
  ptree json;
  json.put("i", 5);
  json.put("b", true);
  json.put("str", "str");
  auto out = cxxJson::Json<TestTypes::FooObject>::deserialize(json);
  TestTypes::FooObject expected{5, true, "str"};
  assert(out == expected);
}
  
```
