#pragma once

/*
 * C++ implementation of LZ-String, version 1.4.4.
 *
 * Based on the LZ-String compression algorithm
 * https://github.com/pieroxy/lz-string
 *
 * MIT Licence
 *
 */

#include <string>
#include <unordered_map>

// preserveall original comments and naming from
// https://github.com/pieroxy/lz-string/blob/master/libs/lz-string.js
namespace lzstring
{
namespace __inner
{
  const std::string keyStrBase64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

  int charCodeAt(const std::string& str, int pos)
  {
    return static_cast<int>(str.at(pos));
  }

  template <typename Fn>
  std::string _compress(const std::string& uncompressed, int bitsPerChar, Fn getCharFromInt)
  {
    int i = 0;
    int value = 0;

    std::unordered_map<std::string, int> context_dictionary;
    std::unordered_map<std::string, bool> context_dictionaryToCreate;

    std::string context_c;
    std::string context_wc;
    std::string context_w;

    int context_enlargeIn = 2; // Compensate for the first entry which should not count
    int context_dictSize = 3;
    int context_numBits = 2;

    std::string context_data;
    int context_data_val = 0;
    int context_data_position = 0;

    for (size_t ii = 0; ii < uncompressed.length(); ++ii)
    {
      context_c = uncompressed.at(ii);
      if (context_dictionary.count(context_c) == 0)
      {
        context_dictionary[context_c] = context_dictSize++;
        context_dictionaryToCreate[context_c] = true;
      }

      context_wc = context_w + context_c;
      if (context_dictionary.count(context_wc) > 0)
      {
        context_w = context_wc;
      }
      else
      {
        auto context_w_it = context_dictionaryToCreate.find(context_w);
        if (context_w_it != context_dictionaryToCreate.end())
        {
          if (charCodeAt(context_w, 0) < 256)
          {
            for (i = 0; i < context_numBits; ++i)
            {
              context_data_val = (context_data_val << 1);
              if (context_data_position == bitsPerChar - 1)
              {
                context_data_position = 0;
                context_data.push_back(getCharFromInt(context_data_val));
                context_data_val = 0;
              }
              else
              {
                ++context_data_position;
              }
            }
            value = charCodeAt(context_w, 0);
            for (i = 0; i < 8; ++i)
            {
              context_data_val = (context_data_val << 1) | (value & 1);

              if (context_data_position == bitsPerChar - 1)
              {
                context_data_position = 0;
                context_data.push_back(getCharFromInt(context_data_val));
                context_data_val = 0;
              }
              else
              {
                ++context_data_position;
              }
              value = value >> 1;
            }
          }
          else
          {
            value = 1;
            for (i = 0; i < context_numBits; ++i)
            {
              context_data_val = (context_data_val << 1) | value;
              if (context_data_position == bitsPerChar - 1)
              {
                context_data_position = 0;
                context_data.push_back(getCharFromInt(context_data_val));
                context_data_val = 0;
              }
              else
              {
                ++context_data_position;
              }
              value = 0;
            }
            value = charCodeAt(context_w, 0);
            for (i = 0; i < 16; ++i)
            {
              context_data_val = (context_data_val << 1) | (value & 1);
              if (context_data_position == bitsPerChar - 1)
              {
                context_data_position = 0;
                context_data.push_back(getCharFromInt(context_data_val));
                context_data_val = 0;
              }
              else
              {
                ++context_data_position;
              }
              value = value >> 1;
            }
          }
          if (--context_enlargeIn == 0)
          {
            context_enlargeIn = 1 << context_numBits; // Math.pow(2, context_numBits);
            ++context_numBits;
          }
          context_dictionaryToCreate.erase(context_w_it); // delete context_dictionaryToCreate[context_w];
        }
        else
        {
          value = context_dictionary[context_w];
          for (i = 0; i < context_numBits; ++i)
          {
            context_data_val = (context_data_val << 1) | (value & 1);
            if (context_data_position == bitsPerChar - 1)
            {
              context_data_position = 0;
              context_data.push_back(getCharFromInt(context_data_val));
              context_data_val = 0;
            }
            else
            {
              ++context_data_position;
            }
            value = value >> 1;
          }
        }
        if (--context_enlargeIn == 0)
        {
          context_enlargeIn = 1 << context_numBits; // Math.pow(2, context_numBits);
          ++context_numBits;
        }
        // Add wc to the dictionary.
        context_dictionary[context_wc] = context_dictSize++;
        context_w = context_c; // context_w = String(context_c);
      }
    }

    // Output the code for w.
    if (!context_w.empty())
    {
      auto context_w_it = context_dictionaryToCreate.find(context_w);
      if (context_w_it != context_dictionaryToCreate.end())
      {
        if (charCodeAt(context_w, 0) < 256)
        {
          for (i = 0; i < context_numBits; ++i)
          {
            context_data_val = (context_data_val << 1);
            if (context_data_position == bitsPerChar - 1)
            {
              context_data_position = 0;
              context_data.push_back(getCharFromInt(context_data_val));
              context_data_val = 0;
            }
            else
            {
              ++context_data_position;
            }
          }
          value = charCodeAt(context_w, 0);
          for (i = 0; i < 8; ++i)
          {
            context_data_val = (context_data_val << 1) | (value & 1);
            if (context_data_position == bitsPerChar - 1)
            {
              context_data_position = 0;
              context_data.push_back(getCharFromInt(context_data_val));
              context_data_val = 0;
            }
            else
            {
              ++context_data_position;
            }
            value = value >> 1;
          }
        }
        else
        {
          value = 1;
          for (i = 0; i < context_numBits; ++i)
          {
            context_data_val = (context_data_val << 1) | value;
            if (context_data_position == bitsPerChar - 1)
            {
              context_data_position = 0;
              context_data.push_back(getCharFromInt(context_data_val));
              context_data_val = 0;
            }
            else
            {
              ++context_data_position;
            }
            value = 0;
          }
          value = charCodeAt(context_w, 0);
          for (i = 0; i < 16; ++i)
          {
            context_data_val = (context_data_val << 1) | (value & 1);
            if (context_data_position == bitsPerChar - 1)
            {
              context_data_position = 0;
              context_data.push_back(getCharFromInt(context_data_val));
              context_data_val = 0;
            }
            else
            {
              ++context_data_position;
            }
            value = value >> 1;
          }
        }
        if (--context_enlargeIn == 0)
        {
          context_enlargeIn = 1 << context_numBits; // Math.pow(2, context_numBits);
          ++context_numBits;
        }
        context_dictionaryToCreate.erase(context_w_it); // delete context_dictionaryToCreate[context_w];
      }
      else
      {
        value = context_dictionary[context_w];
        for (i = 0; i < context_numBits; ++i)
        {
          context_data_val = (context_data_val << 1) | (value & 1);
          if (context_data_position == bitsPerChar - 1)
          {
            context_data_position = 0;
            context_data.push_back(getCharFromInt(context_data_val));
            context_data_val = 0;
          }
          else
          {
            ++context_data_position;
          }
          value = value >> 1;
        }
      }
      if (--context_enlargeIn == 0)
      {
        context_enlargeIn = 1 << context_numBits; // Math.pow(2, context_numBits);
        ++context_numBits;
      }
    }

    // Mark the end of the stream
    value = 2;
    for (i = 0; i < context_numBits; ++i)
    {
      context_data_val = (context_data_val << 1) | (value & 1);
      if (context_data_position == bitsPerChar - 1)
      {
        context_data_position = 0;
        context_data.push_back(getCharFromInt(context_data_val));
        context_data_val = 0;
      }
      else
      {
        ++context_data_position;
      }
      value = value >> 1;
    }

    // Flush the last char
    while (true)
    {
      context_data_val = (context_data_val << 1);
      if (context_data_position == bitsPerChar - 1)
      {
        context_data.push_back(getCharFromInt(context_data_val));
        break;
      }
      else
      {
        ++context_data_position;
      }
    }

    return context_data;
  }
} // namespace __inner

// clang-format off
std::string compressToBase64(const std::string& input)
{
  if (input.empty()) return {};
  using namespace __inner;
  auto res = _compress(input, 6, [](int a) { return keyStrBase64.at(a); });
  switch (res.length() % 4) { // To produce valid Base64
  default: // When could this happen ?
  case 0 : return res;
  case 1 : return res+"===";
  case 2 : return res+"==";
  case 3 : return res+"=";
  }
}
// clang-format on

} // namespace lzstring