# uboone-tutorial
A collection of scripts for the tutorial session of MicroBooNE May 2022 workshop

### Bee Display
```
cd bee_3d/
source runNueApp_original_v1.sh <run_subrun_event_list> data_bnb_mcc9.1_wcp_reco1.5_celltree_merged
python dump_json.py 'bee/nue_*.root' charge cluster flash deadarea charge simple deblob mc vtx
source upload-to-bee.sh to_upload.zip
```

`data_bnb_mcc9.1_wcp_reco1.5_celltree_merged` is the samweb definition for the wirecell reco1.5
"celltree" files and is merged from all existing data set:
```
data_bnb_mcc9.1_wcp_port_TEST_v08_00_00_28_reco1.5_C1_celltree
data_bnb_mcc9.1_wcp_port_TEST_v08_00_00_29_reco1.5_D1_celltree
data_bnb_mcc9.1_wcp_port_TEST_v08_00_00_29_reco1.5_D2_celltree
data_bnb_mcc9.1_wcp_port_TEST_v08_00_00_29_reco1.5_E1_celltree
data_bnb_mcc9.1_wcp_port_TEST_v08_00_00_29_reco1.5_F_celltree
data_bnb_mcc9.1_wcp_port_TEST_v08_00_00_29_reco1.5_G1_celltree
data_bnb_mcc9.1_wcp_port_TEST_v08_00_00_29_reco1.5_G2_celltree
data_bnb_mcc9.1_wcp_port_TEST_v08_00_00_29_reco1.5_G2a_celltree
```

When an overlay event is desired for 3D display, please change the input samweb definition with
a proper "wcp_celltree" definition from this page:
https://microboone-exp.fnal.gov/at_work/AnalysisTools/mc/mcc9.0/details_wcp_v28.html
