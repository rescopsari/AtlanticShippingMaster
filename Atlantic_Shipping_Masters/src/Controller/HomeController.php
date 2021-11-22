<?php


namespace App\Controller;
use App\Entity\Distances;
use App\Entity\Port;
use App\Repository\DistancesRepository;
use App\Repository\PortRepository;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController as AbstractController;
use Symfony\Component\Routing\Annotation\Route;
use Symfony\Component\HttpFoundation\Response;
 

class HomeController extends AbstractController
{
    /**
     * @Route("/", name="home")
     */
    public function home() {
        return $this->render('base.html.twig');
    }

    /**
     * @Route("/simulator", name="simulator")
     */
    public function simulator(PortRepository $portRepository, DistancesRepository $distancesRepository) {



        $em = $this->getDoctrine()->getManager();
        exec('ASM_Distance_Calculator.exe', $distances);
        echo "<script> ports = {};\n";
        foreach ($distances as $d) {
            $temp = explode(":", $d);

            echo "ports[\"$temp[0]\"] = {lat : parseFloat(\"$temp[3]\".replace(',', '.')), lng : parseFloat(\"$temp[4]\".replace(',', '.'))};\n";

            $dbDistances = $distancesRepository->findOneBy(array('portDep' => $temp[0], 'portArr' => $temp[1]));
            // $dbDistances2 = $distancesRepository->findOneBy(array('portDep' => $temp[1], 'portArr' => $temp[0]));
            $dbports = $portRepository->findOneBy(array('name' => $temp[0]));
            if ($dbports == null) {
                $port = new Port();
                $port->setName($temp[0])->setLatitude($temp[3])->setLongitude($temp[4]);
                $em->persist($port);
                $em->flush();
            }
            if ($dbDistances == null){
                $distance = new Distances();
                $distance->setPortDep($temp[0])->setPortArr($temp[1])->setDistance(floatval($temp[2]));
                $em->persist($distance);
                $em->flush();
            }
        }
        echo "</script>";
        echo "<script>function cheminList() {";
        if (count($_POST) >= 3) {

            $arguments = " ";
            foreach ($_POST as $data) {
                $arguments .= $data . " ";
            }
            exec('calcul_meilleur_traj.exe' . $arguments, $trajet);

            foreach ($trajet as $t) {
                echo "listPath.push(ports[\"" . $t . "\"]);";
                echo "pathPorts.push(\"" . $t . "\");";
            }
        }
        echo "flightPath.setPath(listPath);}</script>";

        $ports = $portRepository->findAll();
        return $this->render('simulator.html.twig', [
            'ports' => $ports
        ]);
    }

    /**
     * @Route("/atlantic_api", name="api")
     */
    public function api(PortRepository $portRepository){
        $startHarbor = $_GET['startHarbor'];
        $listHarbor = $_GET['listHarbor'];

        //    "miami,le havre,cork,"
        function putHarborInList($listHarbor)
        {
            $pattern = "/[,]+/";
            $harbors = preg_split($pattern, $listHarbor);
            return $harbors;
        }

        $harbors = putHarborInList($listHarbor);
        $arguments = " "; // contient tous les id des ports par lesquelles nous passerons
        $startHarborInfo = $portRepository->findByName($startHarbor);
        $startHarborId = $startHarborInfo[0]->getId();
        $arguments .= $startHarborId . " ";
        //array_push($arguments, $startHarborId);
        dump($harbors);
        foreach($harbors as $stepHarbor){
            $stepHarborInfo = $portRepository->findByName($stepHarbor);
            $stepHarborId = $stepHarborInfo[0]->getId();
            $arguments .= $stepHarborId . " ";
        }
        dump($arguments);
        exec('calcul_meilleur_traj.exe' . $arguments, $trajet);
        $response = new Response(json_encode($trajet));
        $response->headers->set('Content-Type', 'application/json');

        return $response;

    }
}