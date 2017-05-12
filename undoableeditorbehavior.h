#ifndef UNDOABLEEDITORBEHAVIOR_H
#define UNDOABLEEDITORBEHAVIOR_H

#include <QUndoStack>

#include <abstracteditorbehavior.h>

class UndoableEditorBehavior: public AbstractEditorBehavior
{
public:
    UndoableEditorBehavior(QObject *parent = nullptr)
        : AbstractEditorBehavior (parent)
        , m_undoStack ( new QUndoStack ){}

    QFuture<AsyncStatusPointer> performExample1( bool example1 ) Q_DECL_OVERRIDE {
        AsyncExample1Command *command = new AsyncExample1Command ( example1 );
        m_undoStack->push(command);
        return command->redoFuture();
    }

    QFuture<AsyncStatusPointer> performUndo() {
        const AbstractAsyncUndoable *undoable =
            dynamic_cast<const AbstractAsyncUndoable *>(
                    m_undoStack->command( m_undoStack->index() - 1));
        m_undoStack->undo();
        return const_cast<AbstractAsyncUndoable*>(undoable)->undoFuture();
    }

    QFuture<AsyncStatusPointer> performRedo() {
        const AbstractAsyncUndoable *undoable =
            dynamic_cast<const AbstractAsyncUndoable *>(
                    m_undoStack->command( m_undoStack->index() ));
        m_undoStack->redo();
        return const_cast<AbstractAsyncUndoable*>(undoable)->redoFuture();
    }

    bool canRedo() Q_DECL_OVERRIDE { return m_undoStack->canRedo(); }
    bool canUndo() Q_DECL_OVERRIDE { return m_undoStack->canUndo(); }
private:
    QScopedPointer<QUndoStack> m_undoStack;
};

#endif // UNDOABLEEDITORBEHAVIOR_H
