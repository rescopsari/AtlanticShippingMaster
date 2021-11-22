<?php

namespace App\Entity;

use App\Repository\DistancesRepository;
use Doctrine\ORM\Mapping as ORM;

/**
 * @ORM\Entity(repositoryClass=DistancesRepository::class)
 */
class Distances
{
    /**
     * @ORM\Id
     * @ORM\GeneratedValue
     * @ORM\Column(type="integer")
     */
    private $id;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $portDep;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $portArr;

    /**
     * @ORM\Column(type="float")
     */
    private $distance;

    public function getId(): ?int
    {
        return $this->id;
    }

    public function getPortDep(): ?string
    {
        return $this->portDep;
    }

    public function setPortDep(string $portDep): self
    {
        $this->portDep = $portDep;

        return $this;
    }

    public function getPortArr(): ?string
    {
        return $this->portArr;
    }

    public function setPortArr(string $portArr): self
    {
        $this->portArr = $portArr;

        return $this;
    }

    public function getDistance(): ?float
    {
        return $this->distance;
    }

    public function setDistance(float $distance): self
    {
        $this->distance = $distance;

        return $this;
    }
}
