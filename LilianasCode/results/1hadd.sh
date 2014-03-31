#!/bin/bash

list1=`ls pt500_En5TeV_*.root`
list2=`ls pt300_En5TeV_*.root`
list3=`ls pt200_En5TeV_*.root`
list4=`ls pt0_En5TeV_*.root`
list5=`ls pt500_En100TeV_*.root`
list6=`ls pt300_En100TeV_*.root`
list7=`ls pt200_En100TeV_*.root`
list8=`ls pt0_En100TeV_*.root`

hadd pt500_En5TeV.root $list1
hadd pt300_En5TeV.root $list2
hadd pt200_En5TeV.root $list3
hadd pt0_En5TeV.root $list4
hadd pt500_En100TeV.root $list5
hadd pt300_En100TeV.root $list6
hadd pt200_En100TeV.root $list7
hadd pt0_En100TeV.root $list8

