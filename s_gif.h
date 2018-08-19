long gif_safe_info(const MFDB *pic);
long gif_estimate_size(const MFDB *pic, const _WORD palette[][3]);
long gif_write_file(const MFDB *pic, const _WORD palette[][3], void *mem);
