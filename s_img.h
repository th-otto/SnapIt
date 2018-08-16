long img_safe_info(const MFDB *pic);
long img_estimate_size(const MFDB *pic, const _WORD palette[][3]);
long img_write_file(const MFDB *pic, const _WORD palette[][3], void *mem);
