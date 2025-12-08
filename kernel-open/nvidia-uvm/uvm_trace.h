/*******************************************************************************
    Copyright (c) 2024 NVIDIA Corporation

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be
        included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#undef TRACE_SYSTEM
#define TRACE_SYSTEM nvidia_uvm

#if !defined(_UVM_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _UVM_TRACE_H

#include <linux/tracepoint.h>

// Tracepoint for page faults
TRACE_EVENT(uvm_page_fault,
    TP_PROTO(u64 fault_addr, u64 block_start, u32 page_idx,
             u32 new_residency, u32 pid, u64 timestamp),

    TP_ARGS(fault_addr, block_start, page_idx, new_residency, pid, timestamp),

    TP_STRUCT__entry(
        __field(u64, fault_addr)
        __field(u64, block_start)
        __field(u32, page_idx)
        __field(u32, new_residency)
        __field(u32, pid)
        __field(u64, timestamp)
    ),

    TP_fast_assign(
        __entry->fault_addr = fault_addr;
        __entry->block_start = block_start;
        __entry->page_idx = page_idx;
        __entry->new_residency = new_residency;
        __entry->pid = pid;
        __entry->timestamp = timestamp;
    ),

    TP_printk("addr=0x%llx block=0x%llx page_idx=%u residency=%u pid=%u ts=%llu",
              __entry->fault_addr, __entry->block_start, __entry->page_idx,
              __entry->new_residency, __entry->pid, __entry->timestamp)
);

// Tracepoint for prefetch hints
TRACE_EVENT(uvm_page_prefetch,
    TP_PROTO(u64 prefetch_addr, u64 block_start, u32 page_idx,
             u32 dst_residency, u32 count, u32 pid, u64 timestamp),

    TP_ARGS(prefetch_addr, block_start, page_idx, dst_residency, count, pid, timestamp),

    TP_STRUCT__entry(
        __field(u64, prefetch_addr)
        __field(u64, block_start)
        __field(u32, page_idx)
        __field(u32, dst_residency)
        __field(u32, count)
        __field(u32, pid)
        __field(u64, timestamp)
    ),

    TP_fast_assign(
        __entry->prefetch_addr = prefetch_addr;
        __entry->block_start = block_start;
        __entry->page_idx = page_idx;
        __entry->dst_residency = dst_residency;
        __entry->count = count;
        __entry->pid = pid;
        __entry->timestamp = timestamp;
    ),

    TP_printk("addr=0x%llx block=0x%llx page_idx=%u dst=%u count=%u pid=%u ts=%llu",
              __entry->prefetch_addr, __entry->block_start, __entry->page_idx,
              __entry->dst_residency, __entry->count, __entry->pid, __entry->timestamp)
);

#endif /* _UVM_TRACE_H */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_FILE uvm_trace
#include <trace/define_trace.h>
