#include "../src/lz-string.hpp"
#include <iostream>
#include <cassert>

int main()
{
  std::string json = R"([{"n":"ps1.active","q":1,"t":1474356144455,"v":21}])";
  std::string base64 = R"(NobwRAdmBcYA4GcCMA6AhgYwC4EsBuApmADRgCOMSpWlALAOy0DMArAGxK1csul4wAmJAF8AukA=)";

  std::string compressed = lzstring::compressToBase64(json);

  std::cout << std::endl << "json: " << json;
  std::cout << std::endl << "result:   " << compressed;
  std::cout << std::endl << "expected: " << base64;

  const bool expect_true = compressed == base64;
  assert(expect_true);
  std::cout << std::endl << "PASS" << std::flush;
}