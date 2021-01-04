#ifndef IPROCESS_H
#define IPROCESS_H

struct IProcess {
    virtual ~IProcess() = default;
    virtual void Processing() = 0;
};

#endif // IPROCESS_H
