/*
Ejemplo de hilo tomado de:
https://www.fayewilliams.com/2015/03/31/pthreads-tutorial-linux-cpp/
el codigo no es mio, solo lo tomo como referencia para futuras tareas
*/

#include <iostream>
#include "pthread.h"
#include <string>

using namespace std;

#define NUM_THREADS 5

#define BLACK   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"

static pthread_mutex_t MUTEX;

void* PrintAsciiText(void *id)
{
  string colour;

  pthread_mutex_lock(&MUTEX);
  switch((long)id)
  {
    case 0:
      colour = RED;
      break;
    case 1:
      colour = GREEN;
      break;
    case 2:
      colour = YELLOW;
      break;
    case 3:
      colour = BLUE;
      break;
    case 4:
      colour = CYAN;
      break;
    default:
      colour = BLACK;
      break;
  }

  cout << colour << "I'm a new thread, I'm number " << (long)id << BLACK << endl;
  pthread_mutex_unlock(&MUTEX);

  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[NUM_THREADS];

  for (long int i = 0; i < NUM_THREADS; ++i)
  {
    int t = pthread_create(&threads[i], NULL, PrintAsciiText, (void*)i);

    if (t != 0)
    {
      cout << "Error in thread creation: " << t << endl;
    }
  }

  for(int i = 0; i < NUM_THREADS; ++i)
  {
    void* status;
    int t = pthread_join(threads[i], &status);
    if (t != 0)
    {
      cout << "Error in thread join: " << t << endl;
    }
  }

  return 0;
}
