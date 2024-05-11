#ifndef _WAITFORCHANGE_H
#define _WAITFORCHANGE_H

int init_waiter();

int waitforchange(const char *pathname);

int cleanup_waiter();

#endif
