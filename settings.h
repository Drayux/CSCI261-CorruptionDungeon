/* 
 * File:   settings.h
 * Author: Drayux
 *
 * Created on November 29, 2018, 11:45 PM
 */

#ifndef SETTINGS_H
#define SETTINGS_H

class settings {
public:
    settings();
    void load();
    bool isLoaded();

private:
    bool loaded;

};

#endif
