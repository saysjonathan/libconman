#ifndef _CM_YUM_IMPL
#define _CM_YUM_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include "../pkg.h"

#define MAX_RPMQA_LEN	256
#define QUERY_COMMAND	"rpm -qa --qf '%{NAME} %|EPOCH?{%{EPOCH}}:{0}| %{VERSION} %{RELEASE} %{ARCH}\\n'"
#define INSTALL_COMMAND	"yum install -d 0 -e 0 -y"
#define REMOVE_COMMAND	"yum remove -d 0 -e 0 -y"

#ifdef __cplusplus
}
#endif
#endif
