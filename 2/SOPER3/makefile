CC = gcc 
CFLAGS = -g
LDFLAGS = -lrt -lm -pthread
BINARIOS = mq_receptor mq_sender shm_concurrence shm_concurrence_solved shm_reader shm_writer shm_producer shm_consumer mq_injector mq_workers_pool

all : bins

.PHONY : clean
clean :
	rm -f *.o core $(BINARIOS)
bins:
	$(CC) -c mq_receptor.c -o mq_receptor.o $(CFLAGS) $(LDFLAGS)
	$(CC) mq_receptor.o -o mq_receptor $(LDFLAGS)
	$(CC) -c mq_sender.c -o mq_sender.o $(CFLAGS) $(LDFLAGS)
	$(CC) mq_sender.o -o mq_sender $(LDFLAGS)
	$(CC) -c shm_concurrence.c -o shm_concurrence.o $(CFLAGS) $(LDFLAGS)
	$(CC) shm_concurrence.o -o shm_concurrence $(LDFLAGS)
	$(CC) -c shm_concurrence_solved.c -o shm_concurrence_solved.o $(CFLAGS) $(LDFLAGS)
	$(CC) shm_concurrence_solved.o -o shm_concurrence_solved $(LDFLAGS)
	$(CC) -c shm_reader.c -o shm_reader.o $(CFLAGS) $(LDFLAGS)
	$(CC) shm_reader.o -o shm_reader $(LDFLAGS)
	$(CC) -c shm_writer.c -o shm_writer.o $(CFLAGS) $(LDFLAGS)
	$(CC) shm_writer.o -o shm_writer $(LDFLAGS)
	$(CC) -c shm_producer.c -o shm_producer.o $(CFLAGS) $(LDFLAGS)
	$(CC) shm_producer.o -o shm_producer $(LDFLAGS)
	$(CC) -c shm_consumer.c -o shm_consumer.o $(CFLAGS) $(LDFLAGS)
	$(CC) shm_consumer.o -o shm_consumer $(LDFLAGS)
	$(CC) -c mq_injector.c -o mq_injector.o $(CFLAGS) $(LDFLAGS)
	$(CC) mq_injector.o -o mq_injector $(LDFLAGS)
	$(CC) -c mq_workers_pool.c -o mq_workers_pool.o $(CFLAGS) $(LDFLAGS)
	$(CC) mq_workers_pool.o -o mq_workers_pool $(LDFLAGS)
