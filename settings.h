/*
 * This program is licensed under the unofficial "don't steal my shit license."
 * Pretty much, don't use my shit without me saying so,
 * because that's not cool.
 */

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

