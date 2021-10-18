#include "time.h"

namespace bobbyicons {
const espgui::Icon<24, 24> time{{
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x5AAE, 0x6B2F, 0x7391, 0x7391, 0x7391, 0x7391, 0x7370, 0x7350, 0x62EF,   // 0x0010 (16) pixels
    0x5AAE, 0x528E, 0xFFC0, 0xFF80, 0xFF80, 0xFF80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x62AE, 0x62EF, 0x8C53,   // 0x0020 (32) pixels
    0x9CD6, 0x9CF6, 0x9D17, 0x9CF6, 0x9CF6, 0x94B5, 0x8C74, 0x8C34, 0x7BB1, 0x83CC, 0xDE85, 0xFFA1, 0xFFA1, 0xFFA1, 0xFFA0, 0x0000,   // 0x0030 (48) pixels
    0x0000, 0x0000, 0x0000, 0x0000, 0x62CE, 0x7370, 0xAD57, 0xAD58, 0x9CD6, 0x9CF5, 0xA515, 0xA514, 0xA535, 0xA535, 0x94B4, 0x8433,   // 0x0040 (64) pixels
    0x9CD2, 0xBDAC, 0xD646, 0xF764, 0xFFA3, 0xFFA2, 0xFFA1, 0xFFA0, 0x0000, 0x0000, 0x0000, 0x62EF, 0x7BD2, 0xAD98, 0xA517, 0xA516,   // 0x0050 (80) pixels
    0xB595, 0xCE57, 0xDE94, 0xDE51, 0xE71A, 0xEF5D, 0xDEDA, 0xC617, 0xBDCF, 0xD668, 0xF749, 0xF76D, 0xFFAB, 0xFFA5, 0xFFA2, 0xFF81,   // 0x0060 (96) pixels
    0x0000, 0x0000, 0x62CE, 0x7BB1, 0xAD57, 0x9D16, 0xAD56, 0xD656, 0xD60F, 0xD5EB, 0xDE2E, 0xC614, 0xCE79, 0xF79D, 0xEF7D, 0xEF5B,   // 0x0070 (112) pixels
    0xEF30, 0xF748, 0xF78F, 0xFFB8, 0xFFB4, 0xFFA9, 0xFFA2, 0xFF81, 0x0000, 0x0000, 0x62EF, 0xA517, 0x9CF6, 0xAD56, 0xDEB8, 0xD5CB,   // 0x0080 (128) pixels
    0xDE70, 0xE6B2, 0xE692, 0xDE92, 0xEF7D, 0xF79E, 0xEF7D, 0xEF7C, 0xF771, 0xFF88, 0xFFAF, 0xFFB7, 0xFFB4, 0xF76A, 0xFF82, 0xFFA1,   // 0x0090 (144) pixels
    0x0000, 0x5A8D, 0x8C33, 0xA537, 0x9CF5, 0xE71B, 0x8BE8, 0x9C8C, 0xDE72, 0xE690, 0xDE6F, 0xDE6F, 0xF7BE, 0xF79E, 0xF79D, 0xEF7C,   // 0x00A0 (160) pixels
    0xF774, 0xF78C, 0xFF8A, 0xFF8D, 0xF76B, 0xEF06, 0xE6E4, 0xFFA0, 0x0000, 0x62EF, 0xA537, 0x8C74, 0xCE59, 0xF79D, 0xE6F8, 0x8C71,   // 0x00B0 (176) pixels
    0x942A, 0xD60E, 0xDE2D, 0xDE2C, 0xF7BE, 0xF7BE, 0xF79D, 0xEF7D, 0xEF5A, 0xF772, 0xF76C, 0xF769, 0xDE87, 0xC5EA, 0x9CCA, 0x0000,   // 0x00C0 (192) pixels
    0x0000, 0x7BD2, 0x9CD6, 0x9CD4, 0xDEFB, 0xF79E, 0xF7BE, 0xF79D, 0x94B1, 0x7B67, 0xCD89, 0xD5CA, 0xF7BE, 0xF79E, 0xF79D, 0xEF7D,   // 0x00D0 (208) pixels
    0xEF5C, 0xEF5A, 0xEF56, 0xEF53, 0xBDD0, 0x8C50, 0x7370, 0x0000, 0x0000, 0x8C33, 0x9475, 0xAD76, 0xEF5D, 0xF79D, 0xF79E, 0xF7BE,   // 0x00E0 (224) pixels
    0xF7BE, 0xA533, 0x7B47, 0xB4E7, 0xE71B, 0xEF7D, 0xEF7D, 0xEF7D, 0xEF5D, 0xE73C, 0xE73C, 0xE71B, 0xD69A, 0x7391, 0x7391, 0x0000,   // 0x00F0 (240) pixels
    0x0000, 0x8C53, 0x8C54, 0xB5B7, 0xE73C, 0xDEFB, 0xF79D, 0xF79E, 0xF7BE, 0xF79E, 0x9CD3, 0x8C71, 0x94B2, 0xC618, 0xEF7D, 0xEF5D,   // 0x0100 (256) pixels
    0xEF5C, 0xE73C, 0xD6BA, 0xDEDA, 0xE71C, 0x7370, 0x7BB2, 0x0000, 0x0000, 0x8433, 0x8433, 0xBDD7, 0xDEDA, 0xC638, 0xEF7D, 0xF79D,   // 0x0110 (272) pixels
    0xF79E, 0xF79D, 0xA534, 0xC618, 0xC618, 0xAD75, 0xEF7D, 0xEF5D, 0xE73C, 0xE73C, 0xC617, 0xD699, 0xE73C, 0x7370, 0x7BD2, 0x0000,   // 0x0120 (288) pixels
    0x0000, 0x83F3, 0x8413, 0xBDD7, 0xEF5C, 0xEF5D, 0xEF7D, 0xEF7D, 0xEF7D, 0xBDD6, 0x0020, 0x630C, 0x8430, 0xD6BA, 0xEF5D, 0xEF5C,   // 0x0130 (304) pixels
    0xE73C, 0xE71C, 0xE71B, 0xDEFB, 0xE71C, 0x7370, 0x73B1, 0x0000, 0x0000, 0x7BB2, 0x8433, 0xAD56, 0xE71B, 0xEF5C, 0xEF5D, 0xEF7D,   // 0x0140 (320) pixels
    0xB596, 0x0000, 0x738E, 0xDEDB, 0xEF7D, 0xEF5D, 0xEF5C, 0xE73C, 0xE73C, 0xE71B, 0xDEFB, 0xE71C, 0xC619, 0x7391, 0x7371, 0x0000,   // 0x0150 (336) pixels
    0x0000, 0x6B0F, 0x8C54, 0x8C53, 0xD6BA, 0xE73C, 0xEF5C, 0xEF5D, 0x7BEF, 0x6B4D, 0xD6BA, 0xEF5C, 0xEF5C, 0xE73C, 0xE73C, 0xE71C,   // 0x0160 (352) pixels
    0xE71B, 0xDEFB, 0xDEFB, 0xE71C, 0x9493, 0x83F3, 0x0000, 0x0000, 0x0000, 0x0000, 0x7BF3, 0x8412, 0xBDD7, 0xE71B, 0xE73C, 0xE73C,   // 0x0170 (368) pixels
    0xE73C, 0xE73C, 0xE73C, 0xE73C, 0xE73C, 0xE73C, 0xE71C, 0xE71B, 0xDEFB, 0xDEFB, 0xDEFB, 0xCE7A, 0x7BD2, 0x7BB2, 0x0000, 0x0000,   // 0x0180 (384) pixels
    0x0000, 0x0000, 0x630F, 0x8413, 0x9473, 0xD69A, 0xE71C, 0xE71C, 0xE71C, 0xE73C, 0xE73C, 0xE73C, 0xE71C, 0xE71C, 0xE71B, 0xDEFB,   // 0x0190 (400) pixels
    0xDEFB, 0xDEDB, 0xDEFB, 0x9CD4, 0x7BD2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7371, 0x83F3, 0x9CD4, 0xD6BA, 0xE71B,   // 0x01A0 (416) pixels
    0xE71B, 0xE71B, 0xE71B, 0xCE79, 0xCE79, 0xDEFB, 0xDEFB, 0xDEFB, 0xDEFB, 0xE73C, 0xAD36, 0x7BB2, 0x6B50, 0x4A2B, 0x0000, 0x0000,   // 0x01B0 (432) pixels
    0x0000, 0x0000, 0x18A3, 0x528D, 0x7BB2, 0x7BD2, 0x94B4, 0xD69A, 0xDEFB, 0xDEFB, 0xDEFB, 0xCE58, 0xCE58, 0xDEFB, 0xDEFB, 0xDEFB,   // 0x01C0 (448) pixels
    0xDEFC, 0x9CD5, 0x73B1, 0x73B1, 0x524C, 0x1062, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2926, 0x526C, 0x7391, 0x7BF3, 0x8C53,   // 0x01D0 (464) pixels
    0xAD56, 0xC639, 0xDEFB, 0xE73C, 0xE73C, 0xE71C, 0xCE59, 0xB597, 0x8C53, 0x7BB2, 0x7391, 0x524C, 0x20E5, 0x0000, 0x0000, 0x0000,   // 0x01E0 (480) pixels
    0x0000, 0x0000, 0x0000, 0x0000, 0x18C4, 0x41EA, 0x630F, 0x7BB2, 0x8434, 0x8413, 0x8C53, 0x8C53, 0x8C53, 0x8C53, 0x8413, 0x8413,   // 0x01F0 (496) pixels
    0x7391, 0x630F, 0x41EA, 0x18A3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2926, 0x524C,   // 0x0200 (512) pixels
    0x5AAE, 0x6B50, 0x7BB2, 0x83F3, 0x83F3, 0x7BB2, 0x6B30, 0x5AAD, 0x524C, 0x2105, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0210 (528) pixels
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x18A3, 0x41C9, 0x4A2B, 0x524C, 0x524C, 0x4A2B, 0x39A9, 0x10A3,   // 0x0220 (544) pixels
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0230 (560) pixels
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0240 (576) pixels
}};
} // namespace
