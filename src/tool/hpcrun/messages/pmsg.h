#ifndef PMSG_H
#define PMSG_H

#include <stdarg.h>

#define DBG_PREFIX(s) DBG_##s
#define CTL_PREFIX(s) CTL_##s

#undef E
#define E(s) DBG_PREFIX(s)
typedef enum {
#include "pmsg.src"
} pmsg_category;

#undef D
#define D(s) CTL_PREFIX(s)
typedef enum {
#include "ctl.src"
} ctl_category;

extern void pmsg_init();
extern void pmsg_fini(void);
extern void csprof_emsg(const char *fmt,...);
extern void csprof_emsg_valist(const char *fmt, va_list args);
extern void csprof_amsg(const char *fmt,...);
extern void csprof_pmsg(pmsg_category flag,const char *fmt,...);
extern void csprof_nmsg(pmsg_category flag,const char *fmt,...);
extern void csprof_stderr_msg(const char *fmt,...);
extern void csprof_exit_on_error(int ret, int ret_expected, const char *fmt,...);
extern int  csprof_ctl(ctl_category flag);
extern int  csprof_logfile_fd(void);

extern void csprof_abort_w_info(void (*info)(void),const char *fmt,...);
extern void __csprof_dc(void);

extern int csprof_below_pmsg_threshold(void);
extern void csprof_up_pmsg_count(void);

#define PMSG_LIMIT(C) if (csprof_below_pmsg_threshold()) C

#define EMSG csprof_emsg
#define EEMSG csprof_stderr_msg
#define AMSG csprof_amsg
#define PMSG(f,...) csprof_pmsg(DBG_PREFIX(f),__VA_ARGS__)
#define TMSG(f,...) csprof_pmsg(DBG_PREFIX(f),#f ": " __VA_ARGS__)
#define NMSG(f,...) csprof_nmsg(DBG_PREFIX(f),#f ": " __VA_ARGS__)
#define EXIT_ON_ERROR(r,e,...) csprof_exit_on_error(r,e,__VA_ARGS__)
#define CTL(f)      csprof_ctl(CTL_PREFIX(f))
#define ENABLED(f)         CTL(f)
#define IF_ENABLED(f)      if ( ENABLED(f) )
#define IF_DISABLED(f) if ( ! ENABLED(f) )

#define csprof_abort(...) csprof_abort_w_info(__csprof_dc,__VA_ARGS__)

#endif // PMSG_H