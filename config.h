#ifndef CONFIG_H
#define CONFIG_H

#include "timer.h"
#include <QStringList>
#include <QDir>

#define PATH_JSON                    ".Data/array.json"
#define PATH_BIN                     ".Data/array.dat"
#define PATH_MONITA                  ".Data/"
#define PATH_CEK_STATUS              "../Service/status_monita.sh"
#define PATH_STATUS                  "../Service/cek_status_monita_service.sh"




class config
{
public:
    config();
};



#endif // CONFIG_H
