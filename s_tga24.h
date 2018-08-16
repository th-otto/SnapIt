long tga24_safe_info(const MFDB *pic);
long tga24_estimate_size(const MFDB *pic, const _WORD palette[][3]);
long tga24_write_file(const MFDB *pic, const _WORD palette[][3], void *mem);
