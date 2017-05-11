#ifndef ASYNCEXAMPLE1COMMAND_H
#define ASYNCEXAMPLE1COMMAND_H

#include <QTimer>

#include <abstractasyncundoable.h>

class AsyncExample1Status: public AbstractAsyncStatus
{
    Q_OBJECT

    Q_PROPERTY(bool example1 READ example1 CONSTANT)
public:
    AsyncExample1Status ( bool success, int extra, bool example1,
                          QObject *parent = nullptr )
        : AbstractAsyncStatus(parent)
        , m_example1 ( example1 )
        , m_success ( success )
        , m_extra ( extra ) {}

    bool example1() { return m_example1; }
    bool success() Q_DECL_OVERRIDE { return m_success; }
    int extra() Q_DECL_OVERRIDE { return m_extra; }

private:
    bool m_example1 = false;
    bool m_success = false;
    int m_extra = -1;
};

class AsyncExample1Command: public AbstractAsyncUndoable
{
public:
    AsyncExample1Command(bool example1, QUndoCommand *parent = nullptr)
        : AbstractAsyncUndoable ( parent ), m_example1(example1) {}

    void undo() Q_DECL_OVERRIDE {
        m_undoFuture->reportStarted();
        QTimer *timer = new QTimer();
        timer->setSingleShot(true);
        QObject::connect(timer, &QTimer::timeout, [=]() {
            QSharedPointer<AbstractAsyncStatus> result;
            result.reset(new AsyncExample1Status ( true, 1, m_example1 ));
            m_undoFuture->reportFinished(&result);
            timer->deleteLater();
        } );
        timer->start(1000);
    }

    void redo() Q_DECL_OVERRIDE {
        m_redoFuture->reportStarted();
        QTimer *timer = new QTimer();
        timer->setSingleShot(true);
        QObject::connect(timer, &QTimer::timeout, [=]() {
            QSharedPointer<AbstractAsyncStatus> result;
            result.reset(new AsyncExample1Status ( true, 2, m_example1 ));
            m_redoFuture->reportFinished(&result);
            timer->deleteLater();
        } );
        timer->start(1000);
    }

private:
    QTimer m_timer;
    bool m_example1;
};

#endif // ASYNCEXAMPLE1COMMAND_H
