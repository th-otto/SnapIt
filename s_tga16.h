long tga16_safe_info(const MFDB *pic);
long tga16_estimate_size(const MFDB *pic, const _WORD palette[][3]);
long tga16_write_file(const MFDB *pic, const _WORD palette[][3], void *mem);
