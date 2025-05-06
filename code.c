#include <stdio.h>
#include <string.h>
typedef enum {
    IDLE,
    CONNECTING,
    TRANSMITTING_DATA,
    DISCONNECTED
} State;

typedef struct {
    State state;
} NetworkProtocolFSM;

void initFSM(NetworkProtocolFSM *fsm) {
    fsm->state = IDLE;  // Initial state
}

void connect(NetworkProtocolFSM *fsm) {
    if (fsm->state == IDLE) {
        printf("Connecting...\n");
        fsm->state = CONNECTING;
    } else {
        printf("Cannot connect. Current state: %d\n", fsm->state);
    }
}

void transmit_data(NetworkProtocolFSM *fsm) {
    if (fsm->state == CONNECTING) {
        printf("Connection established. Transmitting data...\n");
        fsm->state = TRANSMITTING_DATA;
    } else if (fsm->state == TRANSMITTING_DATA) {
        printf("Already transmitting data.\n");
    } else {
        printf("Cannot transmit data. Current state: %d\n", fsm->state);
    }
}

void disconnect(NetworkProtocolFSM *fsm) {
    if (fsm->state == TRANSMITTING_DATA || fsm->state == CONNECTING) {
        printf("Disconnecting...\n");
        fsm->state = DISCONNECTED;
    } else {
        printf("Already disconnected or idle. Current state: %d\n", fsm->state);
    }
}

void reset(NetworkProtocolFSM *fsm) {
    if (fsm->state == DISCONNECTED) {
        printf("Resetting to Idle state...\n");
        fsm->state = IDLE;
    } else {
        printf("Cannot reset. Current state: %d\n", fsm->state);
    }
}

const char* get_state(NetworkProtocolFSM *fsm) {
    switch (fsm->state) {
        case IDLE: return "Idle";
        case CONNECTING: return "Connecting";
        case TRANSMITTING_DATA: return "Transmitting Data";
        case DISCONNECTED: return "Disconnected";
        default: return "Unknown State";
    }
}

// Simulation of the network protocol
void simulate_network_protocol() {
    NetworkProtocolFSM fsm;
    initFSM(&fsm);
    printf("Initial State: %s\n", get_state(&fsm));
    
    // Attempt to connect
    connect(&fsm);  // Transition to Connecting
    printf("Current State: %s\n", get_state(&fsm));
    
    // Attempt to transmit data
    transmit_data(&fsm);  // Transition to Transmitting Data
    printf("Current State: %s\n", get_state(&fsm));
    
    // Attempt to disconnect
    disconnect(&fsm);  // Transition to Disconnected
    printf("Current State: %s\n", get_state(&fsm));
    
    // Attempt to reset
    reset(&fsm);  // Transition back to Idle
    printf("Current State: %s\n", get_state(&fsm));
}

int main() {
    simulate_network_protocol();
 return 0;
}
