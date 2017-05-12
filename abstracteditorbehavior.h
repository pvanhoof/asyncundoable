#ifndef ABSTRACTEDITORBEHAVIOR_H
#define ABSTRACTEDITORBEHAVIOR_H

#include <QObject>
#include <QFuture>

#include <abstractasyncundoable.h>
#include <asyncexample1command.h>

class AbstractEditorBehavior : public QObject
{
    Q_OBJECT
public:
    AbstractEditorBehavior( QObject *parent) : QObject (parent) {}

    virtual QFuture<AsyncStatusPointer> performExample1( bool example1 ) = 0;
    virtual QFuture<AsyncStatusPointer> performUndo() = 0;
    virtual QFuture<AsyncStatusPointer> performRedo() = 0;
    virtual bool canRedo() = 0;
    virtual bool canUndo() = 0;
};

#endif // ABSTRACTEDITORBEHAVIOR_H
