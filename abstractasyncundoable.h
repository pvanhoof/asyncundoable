#ifndef ABSTRACTASYNCUNDOABLE_H
#define ABSTRACTASYNCUNDOABLE_H

#include <QObject>
#include <QUndoCommand>
#include <QFuture>
#include <QSharedPointer>
#include <QScopedPointer>

class AbstractAsyncStatus: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool success READ success CONSTANT)
    Q_PROPERTY(int extra READ extra CONSTANT)
public:
    AbstractAsyncStatus(QObject *parent):QObject (parent) {}
    virtual bool success() = 0;
    virtual int extra() = 0;
};

typedef QSharedPointer<AbstractAsyncStatus> AsyncStatusPointer;

class AbstractAsyncUndoable: public QUndoCommand
{
public:
    AbstractAsyncUndoable( QUndoCommand *parent = nullptr )
        : QUndoCommand ( parent )
        , m_undoFuture ( new QFutureInterface<AsyncStatusPointer>() )
        , m_redoFuture ( new QFutureInterface<AsyncStatusPointer>() ) {}
    QFuture<AsyncStatusPointer> undoFuture()
        { return m_undoFuture->future(); }
    QFuture<AsyncStatusPointer> redoFuture()
        { return m_redoFuture->future(); }

protected:
    QScopedPointer<QFutureInterface<AsyncStatusPointer> > m_undoFuture;
    QScopedPointer<QFutureInterface<AsyncStatusPointer> > m_redoFuture;

};

#endif // ABSTRACTASYNCUNDOABLE_H

