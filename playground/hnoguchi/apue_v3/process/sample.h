#ifndef SAMPLE_H
# define SAMPLE_H

void	err_sys(const char *fmt, ...);

void	TELL_WAIT(void);
void	TELL_PARENT(pid_t pid);
void	WAIT_PARENT(void);
void	TELL_CHILD(pid_t pid);
void	WAIT_CHILD(void);

#endif
