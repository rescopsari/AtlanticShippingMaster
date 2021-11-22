<?php

namespace App\Repository;

use App\Entity\Port;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;

/**
 * @method Port|null find($id, $lockMode = null, $lockVersion = null)
 * @method Port|null findOneBy(array $criteria, array $orderBy = null)
 * @method Port[]    findAll()
 * @method Port[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class PortRepository extends ServiceEntityRepository
{
    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, Port::class);
    }

    // /**
    //  * @return Port[] Returns an array of Port objects
    //  */
    
    public function findByName($value)
    {
        return $this->createQueryBuilder('p')
            ->andWhere('p.name = :val')
            ->setParameter('val', $value)
            ->getQuery()
            ->getResult()
        ;
    }

    

    /*
    public function findOneBySomeField($value): ?Port
    {
        return $this->createQueryBuilder('p')
            ->andWhere('p.exampleField = :val')
            ->setParameter('val', $value)
            ->getQuery()
            ->getOneOrNullResult()
        ;
    }
    */
}
