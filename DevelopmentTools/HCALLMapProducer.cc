#include "HCALLMapProducer.h"
#include "HCALLMapLoader.h"
#include "HCALLMapDumper.h"
#include "HCALLMapChecker.h"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr <<"#Please give at least 2 argument " << "RunMode ProduceMode" << std::endl;
    std::cerr <<"# Valid configurations are " << std::endl;
    std::cerr <<"# ./HCALLMapAnalyzer RunMode PrdMode" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::string PrdMode = argv[2];

  std::cout << "#The valid run modes are: HB, HE, HF, HO" << std::endl;
  std::cout << "#The run mode we have right now is: " << RunMode << std::endl;
  std::cout << "#The valid run modes are: LMap, EMap, FMap" << std::endl;
  std::cout << "#The produce mode we have right now is: " << PrdMode << std::endl;

  HCALLMapLoader myHCALLMapLoader;
  HCALLMapDumper myHCALLMapDumper;
  HCALLMapChecker myHCALLMapChecker;

  if( RunMode == "HB" )
  {
    //HBMappingAlgorithm myHBMappingAlgorithm;
    //myHBMappingAlgorithm.ConstructHBLMapObject();

    ngHBMappingAlgorithm myngHBMappingAlgorithm;
    myngHBMappingAlgorithm.ConstructngHBLMapObject();

    if( PrdMode == "LMap" )
    {
      //myHCALLMapDumper.printHBLMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      //myHCALLMapDumper.makedbHBLMapObject("officialMap/HCALLogicalMap.db", "HBLogicalMap",
      //                                    myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      myHCALLMapDumper.printngHBLMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      //myHCALLMapDumper.printHBEMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      myHCALLMapDumper.printngHBEMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      //myHCALLMapDumper.printHBFrontEndMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      myHCALLMapDumper.printngHBFrontEndMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    }
    return 1;
  }
  else if( RunMode == "HE" )
  {
    ngHEMappingAlgorithm myngHEMappingAlgorithm;
    myngHEMappingAlgorithm.ConstructngHELMapObject();

    if( PrdMode == "LMap" )
    {
      myHCALLMapDumper.printngHELMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
      myHCALLMapDumper.makedbngHELMapObject("officialMap/HCALLogicalMap.db", "ngHELogicalMap",
                                            myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      myHCALLMapDumper.printngHEEMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      myHCALLMapDumper.printngHEFrontEndMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    return 1;
  }
  else if( RunMode == "HF" )
  {
    //HFMappingAlgorithm myHFMappingAlgorithm;
    //myHFMappingAlgorithm.ConstructHFLMapObject();

    //myHCALLMapDumper.printHFLMapObject(myHFMappingAlgorithm.myHFFrontEnd, myHFMappingAlgorithm.myHFBackEnd, myHFMappingAlgorithm.myHFPMTBox, myHFMappingAlgorithm.myHFGeometry, myHFMappingAlgorithm.myHFTriggerTower);
    
    ngHFMappingAlgorithm myngHFMappingAlgorithm;
    myngHFMappingAlgorithm.ConstructngHFLMapObject();
    //myngHFMappingAlgorithm.SplitngHFfromOldHF(myHFMappingAlgorithm.myHFFrontEnd, myHFMappingAlgorithm.myHFBackEnd, myHFMappingAlgorithm.myHFPMTBox, myHFMappingAlgorithm.myHFGeometry, myHFMappingAlgorithm.myHFTriggerTower);

    if( PrdMode == "LMap" )
    {
      myHCALLMapDumper.printngHFLMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
      myHCALLMapDumper.makedbngHFLMapObject("officialMap/HCALLogicalMap.db", "ngHFLogicalMap",
                                            myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      myHCALLMapDumper.printngHFEMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      myHCALLMapDumper.printngHFFrontEndMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    return 1;
  }
  else if( RunMode == "HO" )
  {
    HOMappingAlgorithm myHOMappingAlgorithm;
    //so sorry no HO mapping algorithm for now... in a mess... directly load from generation G mapping algotrithm
    int NChannel = myHCALLMapLoader.GetHOFromLMap("officialMap/HCALmapHO_G.txt", myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
    //myHOMappingAlgorithm.ConstructHOLMapObject();

    if( PrdMode == "LMap" )
    {
      myHCALLMapDumper.printHOLMapObject(myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
      //myHCALLMapDumper.makedbHOLMapObject("officialMap/HCALLogicalMap.db", "HOLogicalMap",
      //                                    myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
    }
    if( PrdMode == "EMap" )
    {
    }
    if( PrdMode == "FMap" )
    {
    }
    return 1;
  }

  else{ std::cout << "#Invalide Run Mode, the the fuck is going on!" << std::endl; return -1; }
  return 0;
}
