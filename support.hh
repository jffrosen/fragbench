#ifndef __SUPPORT_HH__
#define __SUPPORT_HH__

static inline unsigned long long get_total_memory() {
	long pages = sysconf(_SC_PHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	return pages * page_size;
}

#endif
