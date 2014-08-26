#ifndef DEFS_H
#define DEFS_H
//这个文件可能其他模块要用到，所以使用STL/BOOST的数据类型
#include <string>
#include <vector>
using std::vector;
using std::string;

enum OS_DISTRIBUTOR{
    MS_WIN8,
    MS_WIN7,
    MS_VISTA,
    MS_XP,
    MS_SERVER03,
    MS_SERVER08,

    LINUX,
    UNIX
} ;

typedef struct _tagHostInf{
    string strFriendlyName;
    string strAccount; // 主机登陆名
    string strHostName;
    OS_DISTRIBUTOR OS;
    vector<string> ips;//主机IP
}HOSTINFO;


typedef struct _tagGroupInf{
    string strGroupName;
    string strCreater; // 群创建者
    vector<HOSTINFO> members;//群成员
}GROUPINFO;




#endif // DEFS_H
