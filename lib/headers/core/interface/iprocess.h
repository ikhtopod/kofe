#ifndef IPROCESS_H
#define IPROCESS_H


class IProcess {
public:
    virtual ~IProcess() = default;
    virtual void Processing() = 0;
};

#endif // IPROCESS_H
