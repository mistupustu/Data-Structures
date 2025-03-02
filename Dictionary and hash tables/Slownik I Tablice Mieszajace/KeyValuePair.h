#pragma once

class KeyValuePair {
protected:
    int key;
    int value;

public:
    KeyValuePair() {}
    KeyValuePair(int key, int value) : key(key), value(value) {}

    int GetKey() const { return key; }
    int GetValue() const { return value; }
    void SetKey(int key) { this->key = key; }
    void SetValue(int value) { this->value = value; }
};

enum StateOfKeyValuePair {
    NOT_INITIALIZED,
    ADDED,
    DELETED
};

class KeyValuePairOpenAdressing : public KeyValuePair {
private:
    StateOfKeyValuePair state;

public:
    KeyValuePairOpenAdressing() : KeyValuePair(), state(StateOfKeyValuePair::NOT_INITIALIZED) {}

    KeyValuePairOpenAdressing(int key, int value) : KeyValuePair(key, value), state(StateOfKeyValuePair::ADDED) {}

    void SetState(StateOfKeyValuePair newState) {
        state = newState;
    }
    StateOfKeyValuePair GetState() const { return state; }
};

class KeyValuePairCuckoo : public KeyValuePair {
private:
    bool added;

public:
    KeyValuePairCuckoo() : KeyValuePair(), added(false) {}

    KeyValuePairCuckoo(int key, int value) : KeyValuePair(key, value), added(true) {}

    bool GetState() const { return added; }

    void SetState(bool addedState) {
        added = addedState;
    }
};