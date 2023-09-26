FROM cgarcia3/spark-base

ADD master.sh /root

CMD ["/root/master.sh"]