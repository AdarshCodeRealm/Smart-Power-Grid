#ifndef POWERGRID_H
#define POWERGRID_H

#include <Arduino.h>
#include "config.h"

class PowerGrid {
private:
    bool switch1State;
    bool switch2State;
    bool switch3State;
    unsigned long lastSwitchChangeTime;
    bool isInDelay;

public:
    PowerGrid() {
        // Initialize switch states
        switch1State = true;  // S1 starts HIGH (ON)
        switch2State = false; // S2 starts LOW (OFF)
        switch3State = true;  // S3 starts HIGH (ON)
        lastSwitchChangeTime = 0;
        isInDelay = false;
    }

    void begin() {
        // Initialize pins
        pinMode(POWER_SOURCE_PIN, OUTPUT);
        pinMode(SWITCH1_PIN, OUTPUT);
        pinMode(SWITCH2_PIN, OUTPUT);
        pinMode(SWITCH3_PIN, OUTPUT);
        
        // Set initial states
        digitalWrite(POWER_SOURCE_PIN, HIGH);
        updateSwitchStates();
    }

    void updateSwitchStates() {
        digitalWrite(SWITCH1_PIN, switch1State);
        digitalWrite(SWITCH2_PIN, switch2State);
        digitalWrite(SWITCH3_PIN, switch3State);
    }

    void handleArea2PowerLoss() {
        if (!isInDelay) {
            switch1State = false;
            switch2State = true;
            switch3State = true;
            updateSwitchStates();
            startDelay();
        }
    }

    void handleArea3PowerLoss() {
        if (!isInDelay) {
            switch3State = false;
            switch1State = true;
            // S2 state remains unchanged
            updateSwitchStates();
            startDelay();
        }
    }

    void startDelay() {
        lastSwitchChangeTime = millis();
        isInDelay = true;
    }

    void update() {
        if (isInDelay && (millis() - lastSwitchChangeTime >= SWITCH_DELAY)) {
            isInDelay = false;
        }
    }

    // Getters for switch states
    bool getSwitch1State() const { return switch1State; }
    bool getSwitch2State() const { return switch2State; }
    bool getSwitch3State() const { return switch3State; }
    bool getIsInDelay() const { return isInDelay; }

    // Setters for switch states
    void setSwitch1State(bool state) {
        if (!isInDelay) {
            switch1State = state;
            updateSwitchStates();
            startDelay();
        }
    }

    void setSwitch2State(bool state) {
        if (!isInDelay) {
            switch2State = state;
            updateSwitchStates();
            startDelay();
        }
    }

    void setSwitch3State(bool state) {
        if (!isInDelay) {
            switch3State = state;
            updateSwitchStates();
            startDelay();
        }
    }

    // Get power status for each area
    int getArea1Power() const { return analogRead(AREA1_PIN); }
    int getArea2Power() const { return analogRead(AREA2_PIN); }
    int getArea3Power() const { return analogRead(AREA3_PIN); }
    int getArea4Power() const { return analogRead(AREA4_PIN); }

    // Check if an area has power loss
    bool hasArea2PowerLoss() const { return getArea2Power() < POWER_THRESHOLD; }
    bool hasArea3PowerLoss() const { return getArea3Power() < POWER_THRESHOLD; }
};

#endif 