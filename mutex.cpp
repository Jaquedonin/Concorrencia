#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>


using namespace std;


class SimpleThread {

    private:
        /* Mutex de execução das threads */
        mutex hello_mutex;

        /*
         * Entra em espera por um período de tempo entre 0 e 5 segundos. Ao
         * final imprime uma mensagem com o número da thread atual
         */
        void HelloMessage (int thread_no) {

            this_thread::sleep_for(chrono::milliseconds(rand() % 5000));

            hello_mutex.lock();
            cout << "Hello from thread: " << thread_no << endl;
            hello_mutex.unlock();

        }

    public:

        /* Número máximo de threads */
        int N_THREADS = 20;

        /*
         * Cria uma thread através do módulo std::thread do C++
         */
        thread *spawn (int thread_no) {
            return new thread(&SimpleThread::HelloMessage, this, thread_no);
        }
};

int
main (int argc, char* argv[])
{
    /* Cria-se um objeto simples da nossa classe de Threads */
    SimpleThread *simple_thread = new SimpleThread();
    /* Um array para controlar a lista de threads abertas */
    vector<thread *> threads(simple_thread->N_THREADS);

    /* Cria uma thread para cada elemento do array */
    for(int i = 0; i < simple_thread->N_THREADS; i++) {
        threads[i] = simple_thread->spawn(i);
    }
    /* Para cada thread aguarda o final de sua execução */
    for(int i = 0; i < simple_thread->N_THREADS; i++) {
        threads[i]->join();
    }

    return EXIT_SUCCESS;
}