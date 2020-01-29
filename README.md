## HPC leaning records

Here are some of codes saved at my HPC learning.

高性能计算(High Performance Computing)机群，简称HPC机群。构建高性能计算系统的主要目的就是提高运算速度，要达到每秒万亿次级的计算速度，对系统的处理器、内存带宽、运算方式、系统I/O、存储等方面的要求都十分高，这其中的每一个环节都将直接影响到系统的运算速度。这类机群主要解决大规模科学问题的计算和海量数据的处理，如科学研究、气象预报、计算模拟、军事研究、CFD/CAE、生物制药、基因测序、图像处理等等。
信息服务机群的应用范围很广，包括如数据中心、电子政务、电子图书馆、大中型网站、网络游戏、金融电信服务、城域网/校园网、大型邮件系统、VOD、管理信息系统等等。就其实现方式上分，还可以分为负载均衡机群、高可用机群等。

简单的说，高性能计算（High Performance Computing）是计算机科学的一个分支，研究并行算法和开发相关软件，致力于开发高性能计算机（High Performance Computer）。

随着信息化社会的飞速发展，人类对信息处理能力的要求越来越高，不仅石油勘探、气象预报、航天国防、科学研究等需求高性能计算机，而金融、政府信息化、教育、企业、网络游戏等更广泛的领域对高性能计算的需求迅猛增长。
集群分为下面几种

* 主/主 (Active/active)
这是最常用的集群模型，它提供了高可用性，并且在只有一个节点在线时提供可以接受的性能，该模型允许最大程度的利用硬件资源。每个节点都通过网络对客户机提供资源，每个节点的容量被定义好，使得性能达到最优，并且每个节点都可以在故障转移时临时接管另一个节点的工作。所有的服务在故障转移后仍保持可用，但是性能通常都会下降。
* 主/从(Active/passive)
为了提供最大的可用性，以及对性能最小的影响，Active/passive模型需要一个在正常工作时处于备用状态，主节点处理客户机的请求，而备用节点处于空闲状态，当主节点出现故障时，备用节点会接管主节点的工作，继续为客户机提供服务，并且不会有任何性能上影响。
* 混合型(Hybrid)
混合是上面两种模型的结合，只针对关键应用进行故障转移，这样可以对这些应用实现可用性的同时让非关键的应用在正常运作时也可以在服务器上运行。当出现故障时，出现故障的服务器上的不太关键的应用就不可用了，但是那些关键应用会转移到另一个可用的节点上，从而达到性能和容错两方面的平衡。
