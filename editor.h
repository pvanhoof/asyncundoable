#ifndef EDITOR_H
#define EDITOR_H

#include <QFuture>
#include <QFutureWatcher>

#include <abstracteditorbehavior.h>
#include <undoableeditorbehavior.h>

class Editor: public QObject
{
    Q_OBJECT
    Q_PROPERTY(AbstractEditorBehavior* editorBehavior READ editorBehavior CONSTANT)
public:
    Editor(QObject *parent=nullptr) : QObject(parent)
        , m_editorBehavior ( new UndoableEditorBehavior ) { }

    AbstractEditorBehavior* editorBehavior() { return m_editorBehavior.data(); }

    Q_INVOKABLE void example1Async(bool example1) {
        QFutureWatcher<AsyncStatusInstance> *watcher = new QFutureWatcher<AsyncStatusInstance>(this);
        connect(watcher, &QFutureWatcher<AsyncStatusInstance>::finished,
                this, &Editor::onExample1Finished);
        watcher->setFuture ( m_editorBehavior->performExample1(example1) );
    }

    Q_INVOKABLE void undoAsync() {
        if (m_editorBehavior->canUndo()) {
            QFutureWatcher<AsyncStatusInstance> *watcher = new QFutureWatcher<AsyncStatusInstance>(this);
            connect(watcher, &QFutureWatcher<AsyncStatusInstance>::finished,
                    this, &Editor::onUndoFinished);
            watcher->setFuture ( m_editorBehavior->performUndo() );
        }
    }

    Q_INVOKABLE void redoAsync() {
        if (m_editorBehavior->canRedo()) {
            QFutureWatcher<AsyncStatusInstance> *watcher = new QFutureWatcher<AsyncStatusInstance>(this);
            connect(watcher, &QFutureWatcher<AsyncStatusInstance>::finished,
                    this, &Editor::onRedoFinished);
            watcher->setFuture ( m_editorBehavior->performRedo() );
        }
    }


signals:
    void example1Finished( AsyncExample1Status *status );
    void undoFinished( AbstractAsyncStatus *status );
    void redoFinished( AbstractAsyncStatus *status );

private slots:
    void onExample1Finished() {
        QFutureWatcher<AsyncStatusInstance> *watcher =
                dynamic_cast<QFutureWatcher<AsyncStatusInstance>*> (sender());
        emit example1Finished( watcher->result().objectCast<AsyncExample1Status>().data() );
        watcher->deleteLater();
    }
    void onUndoFinished() {
        QFutureWatcher<AsyncStatusInstance> *watcher =
                dynamic_cast<QFutureWatcher<AsyncStatusInstance>*> (sender());
        emit undoFinished( watcher->result().objectCast<AbstractAsyncStatus>().data() );
        watcher->deleteLater();
    }
    void onRedoFinished() {
        QFutureWatcher<AsyncStatusInstance> *watcher =
                dynamic_cast<QFutureWatcher<AsyncStatusInstance>*> (sender());
        emit redoFinished( watcher->result().objectCast<AbstractAsyncStatus>().data() );
        watcher->deleteLater();
    }

private:
    QScopedPointer<AbstractEditorBehavior> m_editorBehavior;

};

#endif // EDITOR_H
