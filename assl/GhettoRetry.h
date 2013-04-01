#ifndef GHETTO_RETRY_H
#define GHETTO_RETRY_H

template<typename TEx, TCall>
void ghettoRetry(TCall tcall, int count = 1) {
    // Retry count number of times
    // Note the last one will throw on failure
    for (int i = 0; i < count - 1; i += 1) {
        try {
            tcall();
            return;
        } catch (const TEx&) { }
    }
    tcall();
}

#endif
