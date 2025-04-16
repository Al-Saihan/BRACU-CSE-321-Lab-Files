#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int student_id = 0;
int waiting_room[3] = {-1, -1, -1};
int students_waiting = 0;
int served_students = 0;
int students_left = 0;

pthread_mutex_t mutex;
sem_t s_sem, t_sem;

void *student_arrival()
{
    sleep((rand() % 2) + 1);

    pthread_mutex_lock(&mutex);
    if (students_waiting < 3)
    {
        printf("Student %d started waiting for consultation.\n\n", student_id);
        waiting_room[students_waiting] = student_id;
        students_waiting++;
        student_id++;
        sem_post(&s_sem);
        pthread_mutex_unlock(&mutex);
        sem_wait(&t_sem);
    }
    else if (students_waiting == 3)
    {
        printf("No chairs remaining in lobby. Student %d Leaving.....\n\n", student_id);
        student_id++;
        students_left++;
        pthread_mutex_unlock(&mutex);
    }
}

void *st_consults()
{
    while (1)
    {
        sem_wait(&s_sem);

        pthread_mutex_lock(&mutex);
        printf("A waiting student started getting consultation.\n");
        int stud = waiting_room[0];

        waiting_room[0] = waiting_room[1];
        waiting_room[1] = waiting_room[2];
        waiting_room[2] = -1;

        students_waiting--;

        printf("Number of students now waiting: %d\n", students_waiting);
        printf("ST giving consultation\n");
        printf("Student %d is getting consultation\n\n", stud);
        sleep(2);
        served_students++;
        printf("Student %d finished getting consultation and left\n", stud);
        printf("Number of served students: %d\n\n", served_students);
        pthread_mutex_unlock(&mutex);

        sem_post(&t_sem);

        pthread_mutex_lock(&mutex);
        if (served_students + students_left == 10)
        {
            break;
        }
        else
        {
            pthread_mutex_unlock(&mutex);
        }
    }
}

int main()
{
    // Random Seed
    srand((int)getpid());

    pthread_t students_thread[10];
    pthread_t t_thread;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&s_sem, 0, 0);
    sem_init(&t_sem, 0, 1);

    pthread_create(&t_thread, NULL, st_consults, NULL);

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&students_thread[i], NULL, student_arrival, NULL);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(students_thread[i], NULL);
    }
    pthread_join(t_thread, NULL);
}
