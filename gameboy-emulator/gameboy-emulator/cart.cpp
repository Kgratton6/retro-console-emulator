#pragma once
#include "common.cpp"

struct rom_header {
	Uint8 entry[4];
	Uint8 logo[0x30];

	char title[16];
	Uint16 new_lic_code;
	Uint8 sgb_flag;
	Uint8 type;
	Uint8 rom_size;
	Uint8 ram_size;
	Uint8 dest_code;
	Uint8 lic_code;
	Uint8 version;
	Uint8 checksum;
	Uint16 global_checksum;
};

struct cartridge {
	char filename[1024];
	Uint32 rom_size;
	Uint8* rom_data;
	rom_header* header;
};

static const char* ROM_TYPES[] = { // TYPES DE ROMS
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0x04 ???",
    "MBC2",
    "MBC2+BATTERY",
    "0x07 ???",
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A ???",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    "0x14 ???",
    "0x15 ???",
    "0x16 ???",
    "0x17 ???",
    "0x18 ???",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0x1F ???",
    "MBC6",
    "0x21 ???",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};

static const char* LIC_CODE[0xA5] = { nullptr };
static void init_lic_code() { // LICENCES
    LIC_CODE[0x00] = "None";
    LIC_CODE[0x01] = "Nintendo R&D1";
    LIC_CODE[0x08] = "Capcom";
    LIC_CODE[0x13] = "Electronic Arts";
    LIC_CODE[0x18] = "Hudson Soft";
    LIC_CODE[0x19] = "b-ai";
    LIC_CODE[0x20] = "kss";
    LIC_CODE[0x22] = "pow";
    LIC_CODE[0x24] = "PCM Complete";
    LIC_CODE[0x25] = "san-x";
    LIC_CODE[0x28] = "Kemco Japan";
    LIC_CODE[0x29] = "seta";
    LIC_CODE[0x30] = "Viacom";
    LIC_CODE[0x31] = "Nintendo";
    LIC_CODE[0x32] = "Bandai";
    LIC_CODE[0x33] = "Ocean/Acclaim";
    LIC_CODE[0x34] = "Konami";
    LIC_CODE[0x35] = "Hector";
    LIC_CODE[0x37] = "Taito";
    LIC_CODE[0x38] = "Hudson";
    LIC_CODE[0x39] = "Banpresto";
    LIC_CODE[0x41] = "Ubi Soft";
    LIC_CODE[0x42] = "Atlus";
    LIC_CODE[0x44] = "Malibu";
    LIC_CODE[0x46] = "angel";
    LIC_CODE[0x47] = "Bullet-Proof";
    LIC_CODE[0x49] = "irem";
    LIC_CODE[0x50] = "Absolute";
    LIC_CODE[0x51] = "Acclaim";
    LIC_CODE[0x52] = "Activision";
    LIC_CODE[0x53] = "American sammy";
    LIC_CODE[0x54] = "Konami";
    LIC_CODE[0x55] = "Hi tech entertainment";
    LIC_CODE[0x56] = "LJN";
    LIC_CODE[0x57] = "Matchbox";
    LIC_CODE[0x58] = "Mattel";
    LIC_CODE[0x59] = "Milton Bradley";
    LIC_CODE[0x60] = "Titus";
    LIC_CODE[0x61] = "Virgin";
    LIC_CODE[0x64] = "LucasArts";
    LIC_CODE[0x67] = "Ocean";
    LIC_CODE[0x69] = "Electronic Arts";
    LIC_CODE[0x70] = "Infogrames";
    LIC_CODE[0x71] = "Interplay";
    LIC_CODE[0x72] = "Broderbund";
    LIC_CODE[0x73] = "sculptured";
    LIC_CODE[0x75] = "sci";
    LIC_CODE[0x78] = "THQ";
    LIC_CODE[0x79] = "Accolade";
    LIC_CODE[0x80] = "misawa";
    LIC_CODE[0x83] = "lozc";
    LIC_CODE[0x86] = "Tokuma Shoten Intermedia";
    LIC_CODE[0x87] = "Tsukuda Original";
    LIC_CODE[0x91] = "Chunsoft";
    LIC_CODE[0x92] = "Video system";
    LIC_CODE[0x93] = "Ocean/Acclaim";
    LIC_CODE[0x95] = "Varie";
    LIC_CODE[0x96] = "Yonezawa/s’pal";
    LIC_CODE[0x97] = "Kaneko";
    LIC_CODE[0x99] = "Pack in soft";
    LIC_CODE[0xA4] = "Konami (Yu-Gi-Oh!)";
}

static cartridge cart_ctx;

const char* cart_lic_name() {
    if (cart_ctx.header->new_lic_code <= 0xA4) {
        return LIC_CODE[cart_ctx.header->lic_code];
    }
    return "UNKNOWN LICENCE";
}

const char* cart_type_name() {
    if (cart_ctx.header->type <= 0x22) {
        return LIC_CODE[cart_ctx.header->type];
    }
    return "UNKNOWN ROM TYPE";
}

bool cart_load(char* cartridge) {

    FILE* fp = fopen(cartridge, "r");

    if (!fp) {
        printf("Failed to open the given ROM.");
        return false;
    }
    printf("Reading ROM...");

    fseek(fp, 0, SEEK_END);
    cart_ctx.rom_size = ftell(fp);
    rewind(fp);

    cart_ctx.rom_data = malloc(cart_ctx.rom_size); // Allocate all rom dynamically 



    return true;
}