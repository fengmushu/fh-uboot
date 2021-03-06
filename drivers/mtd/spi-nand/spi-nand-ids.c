
#if 0
#include <linux/mtd/spi-nand.h>
#endif
#include <linux/log2.h>
#include <linux/string.h>
#include "spi-nand.h"

/**
*  Default OOB area specification layout
*/
static struct nand_ecclayout ecc_layout_64 = {
	.eccbytes = 32,
	.eccpos = {
		8, 9, 10, 11, 12, 13, 14, 15,
		24, 25, 26, 27, 28, 29, 30, 21,
		40, 41, 42, 43, 44, 45, 46, 47,
		56, 57, 58, 59, 60, 61, 62, 63
	},
	.oobavail = 30,
	.oobfree = {
		{
			.offset = 2,
			.length = 6
		}, {
			.offset = 16,
			.length = 8
		}, {
			.offset = 32,
			.length = 8
		}, {
			.offset = 48,
			.length = 8
		},
	}
};

static struct nand_ecclayout ecc_layout_256 = {
	.eccbytes = 128,
	.eccpos = {
		128, 129, 130, 131, 132, 133, 134, 135,
		136, 137, 138, 139, 140, 141, 142, 143,
		144, 145, 146, 147, 148, 149, 150, 151,
		152, 153, 154, 155, 156, 157, 158, 159,
		160, 161, 162, 163, 164, 165, 166, 167,
		168, 169, 170, 171, 172, 173, 174, 175,
		176, 177, 178, 179, 180, 181, 182, 183,
		184, 185, 186, 187, 188, 189, 190, 191,
		192, 193, 194, 195, 196, 197, 198, 199,
		200, 201, 202, 203, 204, 205, 206, 207,
		208, 209, 210, 211, 212, 213, 214, 215,
		216, 217, 218, 219, 220, 221, 222, 223,
		224, 225, 226, 227, 228, 229, 230, 231,
		232, 233, 234, 235, 236, 237, 238, 239,
		240, 241, 242, 243, 244, 245, 246, 247,
		248, 249, 250, 251, 252, 253, 254, 255
	},
	.oobavail = 127,
	.oobfree = { {1, 127} }
};

static struct nand_ecclayout ecc_layout_128 = {
	.eccbytes = 64,
	.eccpos = {
		64, 65, 66, 67, 68, 69, 70, 72,
		72, 73, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87,
		88, 89, 90, 91, 92, 93, 94, 95,
		96, 97, 98, 99, 100, 101, 102, 103,
		104, 105, 106, 107, 108, 109, 110, 111,
		112, 113, 114, 115, 116, 117, 118, 119,
		120, 121, 122, 123, 124, 125, 126, 127,
	},
	.oobavail = 62,
	.oobfree = { {2, 63} }
};

static struct nand_ecclayout default_ecc_layout = {
	.eccbytes = 64,
	.oobavail = 28,
	.oobfree = { { 2, 30 } }
};

static struct spi_nand_flash spi_nand_table[] = {
	{
		.name = "W25N01GV",
		.id_info = {
			.id_addr = 0,
			.id_len = 3,
		},
		.dev_id = {0xEF, 0xAA, 0x21},
		.page_size = 2048,
		.page_spare_size = 64,
		.pages_per_blk = 64,
		.blks_per_chip = 1024,
		.options = 0,
		.ecc_mask = 3,
		.ecc_uncorr = 2,
		.ecc_layout = &ecc_layout_64,
	},
	{
		.name = "MX35LF1GE4AB",
		.id_info = {
			.id_addr = 0,
			.id_len = 2,
		},
		.dev_id = {0xC2, 0x12},
		.page_size = 2048,
		.page_spare_size = 64,
		.pages_per_blk = 64,
		.blks_per_chip = 1024,
		.options = 0,
		.ecc_mask = 3,
		.ecc_uncorr = 2,
	},
	{
		.name = "MX35LF2GE4AB",
		.id_info = {
			.id_addr = 0,
			.id_len = 2,
		},
		.dev_id = {0xC2, 0x22},
		.page_size = 2048,
		.page_spare_size = 64,
		.pages_per_blk = 64,
		.blks_per_chip = 2048,
		.options = SPINAND_NEED_PLANE_SELECT,
		.ecc_mask = 3,
		.ecc_uncorr = 2,
	},
	{
		.name = "GD5F1GQ4U",
		.id_info = {
			.id_addr = SPI_NAND_ID_NO_DUMMY,
			.id_len = 3,
		},
		.dev_id = {0xC8, 0xB1, 0x48},
		.page_size = 2048,
		.page_spare_size = 128,
		.pages_per_blk = 64,
		.blks_per_chip = 1024,
		.options = 0,
		.ecc_mask = 7,
		.ecc_uncorr = 7,
		.ecc_layout = &ecc_layout_128,
	},
	{
		.name = "GD5F2GQ4U",
		.id_info = {
			.id_addr = SPI_NAND_ID_NO_DUMMY,
			.id_len = 3,
		},
		.dev_id = {0xC8, 0xB2, 0x48},
		.page_size = 2048,
		.page_spare_size = 128,
		.pages_per_blk = 64,
		.blks_per_chip = 2048,
		.options = 0,
		.ecc_mask = 7,
		.ecc_uncorr = 7,
		.ecc_layout = &ecc_layout_128,
	},
	{
		.name = NULL,
	}

};

/**
 * spi_nand_scan_id_table - [INTERN] scan chip info in id table
 * @chip: SPI-NAND device structure
 * @id: point to manufacture id and device id
 */
int spi_nand_scan_id_table(struct spi_nand_chip *chip, u8 *id)
{
	int i,j=0;
	struct spi_nand_flash *type = spi_nand_table;

	for (; type->name; type++) {
//		if (id[0] == type->mfr_id && id[1] == type->dev_id) {
		for (j=0, i = (SPI_NAND_ID_NO_DUMMY == type->id_info.id_addr) ? 0 : 1;
		                j < type->id_info.id_len;j++,i++ ) {
			if (id[i] != type->dev_id[j])
				break;
		}
		if (j == type->id_info.id_len) {
			chip->name = type->name;
			chip->size = type->page_size * type->pages_per_blk
			                * type->blks_per_chip;
			chip->block_size = type->page_size
			                * type->pages_per_blk;
			chip->page_size = type->page_size;
			chip->page_spare_size = type->page_spare_size;
			chip->block_shift = ilog2(chip->block_size);
			chip->page_shift = ilog2(chip->page_size);
			chip->page_mask = chip->page_size - 1;
			chip->options = type->options;
			if (!type->ecc_layout)
				chip->ecclayout = &default_ecc_layout;
			else
				chip->ecclayout = type->ecc_layout;
			chip->dev_id_len = type->id_info.id_len;
			chip->ecc_uncorr = type->ecc_uncorr;
			chip->ecc_mask = type->ecc_mask;
			memcpy(chip->dev_id, type->dev_id, chip->dev_id_len);

			return 1;
		}
	}

	return 0;
}
