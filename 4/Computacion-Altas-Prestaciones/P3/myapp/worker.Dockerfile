FROM cgarcia3/spark-base

ADD worker.sh /root

CMD ["/root/worker.sh"]