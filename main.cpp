#include "user.h"

int main(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    login_trading obj;
    obj.home();
    
    curl_global_cleanup();
    
    return 0;
}