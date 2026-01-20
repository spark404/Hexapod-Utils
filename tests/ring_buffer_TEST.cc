//
// Created by Hugo Trippaers on 18/04/2025.
//

#include <gtest/gtest.h>

#include "ring_buffer.h"

class RingBufferTest : public testing::Test {
protected:
    static constexpr size_t BUFFER_SIZE = 16;
    uint8_t buffer[BUFFER_SIZE]{};
    ringbuf_t rb{};

    void SetUp() override {
        ringbuf_init(&rb, buffer, BUFFER_SIZE);
    }
};

TEST_F(RingBufferTest, Init) {
    EXPECT_EQ(ringbuf_available(&rb), 0);
    EXPECT_EQ(ringbuf_free(&rb), BUFFER_SIZE - 1);
}

TEST_F(RingBufferTest, PushPop) {
    uint8_t val = 42;
    uint8_t out = 0;

    EXPECT_TRUE(ringbuf_push(&rb, val));
    EXPECT_EQ(ringbuf_available(&rb), 1);
    
    EXPECT_TRUE(ringbuf_pop(&rb, &out));
    EXPECT_EQ(out, val);
    EXPECT_EQ(ringbuf_available(&rb), 0);
}

TEST_F(RingBufferTest, FullBuffer) {
    // Fill the buffer (capacity is size - 1)
    for (size_t i = 0; i < BUFFER_SIZE - 1; ++i) {
        EXPECT_TRUE(ringbuf_push(&rb, (uint8_t)i));
    }

    EXPECT_EQ(ringbuf_free(&rb), 0);
    EXPECT_FALSE(ringbuf_push(&rb, 100)); // Should be full
}

TEST_F(RingBufferTest, ReadWrite) {
    const uint8_t data[] = {1, 2, 3, 4, 5};
    uint8_t output[5] = {0};

    EXPECT_EQ(ringbuf_write(&rb, data, 5), 5);
    EXPECT_EQ(ringbuf_available(&rb), 5);

    EXPECT_EQ(ringbuf_read(&rb, output, 5), 5);
    EXPECT_EQ(memcmp(data, output, 5), 0);
    EXPECT_EQ(ringbuf_available(&rb), 0);
}

TEST_F(RingBufferTest, WrapAround) {
    // Move pointers near the end
    for (size_t i = 0; i < BUFFER_SIZE - 2; ++i) {
        ringbuf_push(&rb, 0);
        uint8_t dummy;
        ringbuf_pop(&rb, &dummy);
    }

    // Now write across the wrap-around point
    uint8_t data[] = {10, 20, 30};
    EXPECT_EQ(ringbuf_write(&rb, data, 3), 3);
    
    uint8_t output[3];
    EXPECT_EQ(ringbuf_read(&rb, output, 3), 3);
    EXPECT_EQ(output[0], 10);
    EXPECT_EQ(output[1], 20);
    EXPECT_EQ(output[2], 30);
}

TEST_F(RingBufferTest, Reset) {
    ringbuf_push(&rb, 1);
    ringbuf_push(&rb, 2);
    ringbuf_reset(&rb);

    EXPECT_EQ(ringbuf_available(&rb), 0);
    uint8_t dummy;
    EXPECT_FALSE(ringbuf_pop(&rb, &dummy));
}
