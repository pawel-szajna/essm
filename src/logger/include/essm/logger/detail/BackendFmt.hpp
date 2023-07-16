#pragma once

#include <fmt/color.h>

#include <essm/logger/detail/Filename.hpp>

// TODO: Extract this to a common place, again

namespace essm::detail
{
constexpr uint32_t crc32_[]{
    0x00'00'00'00, 0x77'07'30'96, 0xee'0e'61'2c, 0x99'09'51'ba, 0x07'6d'c4'19, 0x70'6a'f4'8f, 0xe9'63'a5'35,
    0x9e'64'95'a3, 0x0e'db'88'32, 0x79'dc'b8'a4, 0xe0'd5'e9'1e, 0x97'd2'd9'88, 0x09'b6'4c'2b, 0x7e'b1'7c'bd,
    0xe7'b8'2d'07, 0x90'bf'1d'91, 0x1d'b7'10'64, 0x6a'b0'20'f2, 0xf3'b9'71'48, 0x84'be'41'de, 0x1a'da'd4'7d,
    0x6d'dd'e4'eb, 0xf4'd4'b5'51, 0x83'd3'85'c7, 0x13'6c'98'56, 0x64'6b'a8'c0, 0xfd'62'f9'7a, 0x8a'65'c9'ec,
    0x14'01'5c'4f, 0x63'06'6c'd9, 0xfa'0f'3d'63, 0x8d'08'0d'f5, 0x3b'6e'20'c8, 0x4c'69'10'5e, 0xd5'60'41'e4,
    0xa2'67'71'72, 0x3c'03'e4'd1, 0x4b'04'd4'47, 0xd2'0d'85'fd, 0xa5'0a'b5'6b, 0x35'b5'a8'fa, 0x42'b2'98'6c,
    0xdb'bb'c9'd6, 0xac'bc'f9'40, 0x32'd8'6c'e3, 0x45'df'5c'75, 0xdc'd6'0d'cf, 0xab'd1'3d'59, 0x26'd9'30'ac,
    0x51'de'00'3a, 0xc8'd7'51'80, 0xbf'd0'61'16, 0x21'b4'f4'b5, 0x56'b3'c4'23, 0xcf'ba'95'99, 0xb8'bd'a5'0f,
    0x28'02'b8'9e, 0x5f'05'88'08, 0xc6'0c'd9'b2, 0xb1'0b'e9'24, 0x2f'6f'7c'87, 0x58'68'4c'11, 0xc1'61'1d'ab,
    0xb6'66'2d'3d, 0x76'dc'41'90, 0x01'db'71'06, 0x98'd2'20'bc, 0xef'd5'10'2a, 0x71'b1'85'89, 0x06'b6'b5'1f,
    0x9f'bf'e4'a5, 0xe8'b8'd4'33, 0x78'07'c9'a2, 0x0f'00'f9'34, 0x96'09'a8'8e, 0xe1'0e'98'18, 0x7f'6a'0d'bb,
    0x08'6d'3d'2d, 0x91'64'6c'97, 0xe6'63'5c'01, 0x6b'6b'51'f4, 0x1c'6c'61'62, 0x85'65'30'd8, 0xf2'62'00'4e,
    0x6c'06'95'ed, 0x1b'01'a5'7b, 0x82'08'f4'c1, 0xf5'0f'c4'57, 0x65'b0'd9'c6, 0x12'b7'e9'50, 0x8b'be'b8'ea,
    0xfc'b9'88'7c, 0x62'dd'1d'df, 0x15'da'2d'49, 0x8c'd3'7c'f3, 0xfb'd4'4c'65, 0x4d'b2'61'58, 0x3a'b5'51'ce,
    0xa3'bc'00'74, 0xd4'bb'30'e2, 0x4a'df'a5'41, 0x3d'd8'95'd7, 0xa4'd1'c4'6d, 0xd3'd6'f4'fb, 0x43'69'e9'6a,
    0x34'6e'd9'fc, 0xad'67'88'46, 0xda'60'b8'd0, 0x44'04'2d'73, 0x33'03'1d'e5, 0xaa'0a'4c'5f, 0xdd'0d'7c'c9,
    0x50'05'71'3c, 0x27'02'41'aa, 0xbe'0b'10'10, 0xc9'0c'20'86, 0x57'68'b5'25, 0x20'6f'85'b3, 0xb9'66'd4'09,
    0xce'61'e4'9f, 0x5e'de'f9'0e, 0x29'd9'c9'98, 0xb0'd0'98'22, 0xc7'd7'a8'b4, 0x59'b3'3d'17, 0x2e'b4'0d'81,
    0xb7'bd'5c'3b, 0xc0'ba'6c'ad, 0xed'b8'83'20, 0x9a'bf'b3'b6, 0x03'b6'e2'0c, 0x74'b1'd2'9a, 0xea'd5'47'39,
    0x9d'd2'77'af, 0x04'db'26'15, 0x73'dc'16'83, 0xe3'63'0b'12, 0x94'64'3b'84, 0x0d'6d'6a'3e, 0x7a'6a'5a'a8,
    0xe4'0e'cf'0b, 0x93'09'ff'9d, 0x0a'00'ae'27, 0x7d'07'9e'b1, 0xf0'0f'93'44, 0x87'08'a3'd2, 0x1e'01'f2'68,
    0x69'06'c2'fe, 0xf7'62'57'5d, 0x80'65'67'cb, 0x19'6c'36'71, 0x6e'6b'06'e7, 0xfe'd4'1b'76, 0x89'd3'2b'e0,
    0x10'da'7a'5a, 0x67'dd'4a'cc, 0xf9'b9'df'6f, 0x8e'be'ef'f9, 0x17'b7'be'43, 0x60'b0'8e'd5, 0xd6'd6'a3'e8,
    0xa1'd1'93'7e, 0x38'd8'c2'c4, 0x4f'df'f2'52, 0xd1'bb'67'f1, 0xa6'bc'57'67, 0x3f'b5'06'dd, 0x48'b2'36'4b,
    0xd8'0d'2b'da, 0xaf'0a'1b'4c, 0x36'03'4a'f6, 0x41'04'7a'60, 0xdf'60'ef'c3, 0xa8'67'df'55, 0x31'6e'8e'ef,
    0x46'69'be'79, 0xcb'61'b3'8c, 0xbc'66'83'1a, 0x25'6f'd2'a0, 0x52'68'e2'36, 0xcc'0c'77'95, 0xbb'0b'47'03,
    0x22'02'16'b9, 0x55'05'26'2f, 0xc5'ba'3b'be, 0xb2'bd'0b'28, 0x2b'b4'5a'92, 0x5c'b3'6a'04, 0xc2'd7'ff'a7,
    0xb5'd0'cf'31, 0x2c'd9'9e'8b, 0x5b'de'ae'1d, 0x9b'64'c2'b0, 0xec'63'f2'26, 0x75'6a'a3'9c, 0x02'6d'93'0a,
    0x9c'09'06'a9, 0xeb'0e'36'3f, 0x72'07'67'85, 0x05'00'57'13, 0x95'bf'4a'82, 0xe2'b8'7a'14, 0x7b'b1'2b'ae,
    0x0c'b6'1b'38, 0x92'd2'8e'9b, 0xe5'd5'be'0d, 0x7c'dc'ef'b7, 0x0b'db'df'21, 0x86'd3'd2'd4, 0xf1'd4'e2'42,
    0x68'dd'b3'f8, 0x1f'da'83'6e, 0x81'be'16'cd, 0xf6'b9'26'5b, 0x6f'b0'77'e1, 0x18'b7'47'77, 0x88'08'5a'e6,
    0xff'0f'6a'70, 0x66'06'3b'ca, 0x11'01'0b'5c, 0x8f'65'9e'ff, 0xf8'62'ae'69, 0x61'6b'ff'd3, 0x16'6c'cf'45,
    0xa0'0a'e2'78, 0xd7'0d'd2'ee, 0x4e'04'83'54, 0x39'03'b3'c2, 0xa7'67'26'61, 0xd0'60'16'f7, 0x49'69'47'4d,
    0x3e'6e'77'db, 0xae'd1'6a'4a, 0xd9'd6'5a'dc, 0x40'df'0b'66, 0x37'd8'3b'f0, 0xa9'bc'ae'53, 0xde'bb'9e'c5,
    0x47'b2'cf'7f, 0x30'b5'ff'e9, 0xbd'bd'f2'1c, 0xca'ba'c2'8a, 0x53'b3'93'30, 0x24'b4'a3'a6, 0xba'd0'36'05,
    0xcd'd7'06'93, 0x54'de'57'29, 0x23'd9'67'bf, 0xb3'66'7a'2e, 0xc4'61'4a'b8, 0x5d'68'1b'02, 0x2a'6f'2b'94,
    0xb4'0b'be'37, 0xc3'0c'8e'a1, 0x5a'05'df'1b, 0x2d'02'ef'8d};

consteval uint32_t hash_(::std::string_view input)
{
    uint32_t result = 0xff'ff'ff'ff;
    for (auto character : input)
    {
        result = (result >> 8) ^ crc32_[(result ^ character) & 0xff];
    }
    return result ^ 0xff'ff'ff'ff;
}
} // namespace essm::detail

#define __essm_logger_command(app, level, fheader, ...)                                                                \
    (::fmt::print(fheader, "{}", #level),                                                                              \
     ::fmt::print("/"),                                                                                                \
     ::fmt::print(fmt::fg(::fmt::rgb(::essm::detail::hash_(#app) | 0x88'88'88)), "{} ", app),                          \
     ::fmt::print(fmt::emphasis::bold, "[{}:{}] ", __essm_logger_filename, __LINE__),                                  \
     ::fmt::print(__VA_ARGS__),                                                                                        \
     ::fmt::print("\n"))

#define __essm_logger_debug(app, ...) __essm_logger_command(app, DBG, fmt::fg(fmt::color::sea_green), __VA_ARGS__)
#define __essm_logger_info(app, ...) __essm_logger_command(app, INF, fmt::fg(fmt::color::lime_green), __VA_ARGS__)
#define __essm_logger_warn(app, ...) __essm_logger_command(app, WRN, fmt::fg(fmt::color::red), __VA_ARGS__)
#define __essm_logger_error(app, ...) __essm_logger_command(app, ERR, fmt::bg(fmt::color::red), __VA_ARGS__)
