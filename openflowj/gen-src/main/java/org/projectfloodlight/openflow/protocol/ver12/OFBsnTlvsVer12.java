// Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University
// Copyright (c) 2011, 2012 Open Networking Foundation
// Copyright (c) 2012, 2013 Big Switch Networks, Inc.
// This library was generated by the LoxiGen Compiler.
// See the file LICENSE.txt which should have been included in the source distribution

// Automatically generated by LOXI from template of_factory_class.java
// Do not modify

package org.projectfloodlight.openflow.protocol.ver12;

import org.projectfloodlight.openflow.protocol.*;
import org.projectfloodlight.openflow.protocol.action.*;
import org.projectfloodlight.openflow.protocol.actionid.*;
import org.projectfloodlight.openflow.protocol.bsntlv.*;
import org.projectfloodlight.openflow.protocol.errormsg.*;
import org.projectfloodlight.openflow.protocol.meterband.*;
import org.projectfloodlight.openflow.protocol.instruction.*;
import org.projectfloodlight.openflow.protocol.instructionid.*;
import org.projectfloodlight.openflow.protocol.match.*;
import org.projectfloodlight.openflow.protocol.oxm.*;
import org.projectfloodlight.openflow.protocol.queueprop.*;
import org.projectfloodlight.openflow.types.*;
import org.projectfloodlight.openflow.util.*;
import org.projectfloodlight.openflow.exceptions.*;


public class OFBsnTlvsVer12 implements OFBsnTlvs {
    public final static OFBsnTlvsVer12 INSTANCE = new OFBsnTlvsVer12();




    public OFBsnTlvBroadcastQueryTimeout.Builder buildBroadcastQueryTimeout() {
        throw new UnsupportedOperationException("OFBsnTlvBroadcastQueryTimeout not supported in version 1.2");
    }
    public OFBsnTlvBroadcastQueryTimeout broadcastQueryTimeout(long value) {
        throw new UnsupportedOperationException("OFBsnTlvBroadcastQueryTimeout not supported in version 1.2");
    }

    public OFBsnTlvCircuitId.Builder buildCircuitId() {
        throw new UnsupportedOperationException("OFBsnTlvCircuitId not supported in version 1.2");
    }
    public OFBsnTlvCircuitId circuitId(byte[] value) {
        throw new UnsupportedOperationException("OFBsnTlvCircuitId not supported in version 1.2");
    }

    public OFBsnTlvIdleNotification idleNotification() {
        throw new UnsupportedOperationException("OFBsnTlvIdleNotification not supported in version 1.2");
    }

    public OFBsnTlvIdleTime.Builder buildIdleTime() {
        throw new UnsupportedOperationException("OFBsnTlvIdleTime not supported in version 1.2");
    }
    public OFBsnTlvIdleTime idleTime(U64 value) {
        throw new UnsupportedOperationException("OFBsnTlvIdleTime not supported in version 1.2");
    }

    public OFBsnTlvIdleTimeout.Builder buildIdleTimeout() {
        throw new UnsupportedOperationException("OFBsnTlvIdleTimeout not supported in version 1.2");
    }
    public OFBsnTlvIdleTimeout idleTimeout(long value) {
        throw new UnsupportedOperationException("OFBsnTlvIdleTimeout not supported in version 1.2");
    }

    public OFBsnTlvIpv4.Builder buildIpv4() {
        throw new UnsupportedOperationException("OFBsnTlvIpv4 not supported in version 1.2");
    }
    public OFBsnTlvIpv4 ipv4(IPv4Address value) {
        throw new UnsupportedOperationException("OFBsnTlvIpv4 not supported in version 1.2");
    }

    public OFBsnTlvMac.Builder buildMac() {
        throw new UnsupportedOperationException("OFBsnTlvMac not supported in version 1.2");
    }
    public OFBsnTlvMac mac(MacAddress value) {
        throw new UnsupportedOperationException("OFBsnTlvMac not supported in version 1.2");
    }

    public OFBsnTlvMissPackets.Builder buildMissPackets() {
        throw new UnsupportedOperationException("OFBsnTlvMissPackets not supported in version 1.2");
    }
    public OFBsnTlvMissPackets missPackets(U64 value) {
        throw new UnsupportedOperationException("OFBsnTlvMissPackets not supported in version 1.2");
    }

    public OFBsnTlvPort.Builder buildPort() {
        throw new UnsupportedOperationException("OFBsnTlvPort not supported in version 1.2");
    }
    public OFBsnTlvPort port(OFPort value) {
        throw new UnsupportedOperationException("OFBsnTlvPort not supported in version 1.2");
    }

    public OFBsnTlvQueueId.Builder buildQueueId() {
        throw new UnsupportedOperationException("OFBsnTlvQueueId not supported in version 1.2");
    }
    public OFBsnTlvQueueId queueId(long value) {
        throw new UnsupportedOperationException("OFBsnTlvQueueId not supported in version 1.2");
    }

    public OFBsnTlvQueueWeight.Builder buildQueueWeight() {
        throw new UnsupportedOperationException("OFBsnTlvQueueWeight not supported in version 1.2");
    }
    public OFBsnTlvQueueWeight queueWeight(long value) {
        throw new UnsupportedOperationException("OFBsnTlvQueueWeight not supported in version 1.2");
    }

    public OFBsnTlvReplyPackets.Builder buildReplyPackets() {
        throw new UnsupportedOperationException("OFBsnTlvReplyPackets not supported in version 1.2");
    }
    public OFBsnTlvReplyPackets replyPackets(U64 value) {
        throw new UnsupportedOperationException("OFBsnTlvReplyPackets not supported in version 1.2");
    }

    public OFBsnTlvRequestPackets.Builder buildRequestPackets() {
        throw new UnsupportedOperationException("OFBsnTlvRequestPackets not supported in version 1.2");
    }
    public OFBsnTlvRequestPackets requestPackets(U64 value) {
        throw new UnsupportedOperationException("OFBsnTlvRequestPackets not supported in version 1.2");
    }

    public OFBsnTlvRxPackets.Builder buildRxPackets() {
        throw new UnsupportedOperationException("OFBsnTlvRxPackets not supported in version 1.2");
    }
    public OFBsnTlvRxPackets rxPackets(U64 value) {
        throw new UnsupportedOperationException("OFBsnTlvRxPackets not supported in version 1.2");
    }

    public OFBsnTlvTxPackets.Builder buildTxPackets() {
        throw new UnsupportedOperationException("OFBsnTlvTxPackets not supported in version 1.2");
    }
    public OFBsnTlvTxPackets txPackets(U64 value) {
        throw new UnsupportedOperationException("OFBsnTlvTxPackets not supported in version 1.2");
    }

    public OFBsnTlvUdfAnchor.Builder buildUdfAnchor() {
        throw new UnsupportedOperationException("OFBsnTlvUdfAnchor not supported in version 1.2");
    }
    public OFBsnTlvUdfAnchor udfAnchor(OFBsnUdfAnchor value) {
        throw new UnsupportedOperationException("OFBsnTlvUdfAnchor not supported in version 1.2");
    }

    public OFBsnTlvUdfId.Builder buildUdfId() {
        throw new UnsupportedOperationException("OFBsnTlvUdfId not supported in version 1.2");
    }
    public OFBsnTlvUdfId udfId(int value) {
        throw new UnsupportedOperationException("OFBsnTlvUdfId not supported in version 1.2");
    }

    public OFBsnTlvUdfLength.Builder buildUdfLength() {
        throw new UnsupportedOperationException("OFBsnTlvUdfLength not supported in version 1.2");
    }
    public OFBsnTlvUdfLength udfLength(int value) {
        throw new UnsupportedOperationException("OFBsnTlvUdfLength not supported in version 1.2");
    }

    public OFBsnTlvUdfOffset.Builder buildUdfOffset() {
        throw new UnsupportedOperationException("OFBsnTlvUdfOffset not supported in version 1.2");
    }
    public OFBsnTlvUdfOffset udfOffset(int value) {
        throw new UnsupportedOperationException("OFBsnTlvUdfOffset not supported in version 1.2");
    }

    public OFBsnTlvUnicastQueryTimeout.Builder buildUnicastQueryTimeout() {
        throw new UnsupportedOperationException("OFBsnTlvUnicastQueryTimeout not supported in version 1.2");
    }
    public OFBsnTlvUnicastQueryTimeout unicastQueryTimeout(long value) {
        throw new UnsupportedOperationException("OFBsnTlvUnicastQueryTimeout not supported in version 1.2");
    }

    public OFBsnTlvVlanVid.Builder buildVlanVid() {
        throw new UnsupportedOperationException("OFBsnTlvVlanVid not supported in version 1.2");
    }
    public OFBsnTlvVlanVid vlanVid(VlanVid value) {
        throw new UnsupportedOperationException("OFBsnTlvVlanVid not supported in version 1.2");
    }

    public OFBsnTlvVrf.Builder buildVrf() {
        throw new UnsupportedOperationException("OFBsnTlvVrf not supported in version 1.2");
    }
    public OFBsnTlvVrf vrf(long value) {
        throw new UnsupportedOperationException("OFBsnTlvVrf not supported in version 1.2");
    }

    public OFMessageReader<OFBsnTlv> getReader() {
        throw new UnsupportedOperationException("Reader<OFBsnTlv> not supported in version 1.2");
    }


    public OFVersion getVersion() {
            return OFVersion.OF_12;
    }
}
