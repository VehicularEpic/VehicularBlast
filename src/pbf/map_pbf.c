/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * This file was generated by pbtools.
 */

#include <limits.h>
#include "veb/pbf/map_pbf.h"

#if CHAR_BIT != 8
#    error "Number of bits in a char must be 8."
#endif

void map_entity_init(
    struct map_entity_t *self_p,
    struct pbtools_heap_t *heap_p)
{
    self_p->base.heap_p = heap_p;
    self_p->i = 0;
    self_p->position.length = 0;
    self_p->rotation.length = 0;
}

void map_entity_encode_inner(
    struct pbtools_encoder_t *encoder_p,
    struct map_entity_t *self_p)
{
    pbtools_encoder_write_repeated_float(encoder_p, 3, &self_p->rotation);
    pbtools_encoder_write_repeated_float(encoder_p, 2, &self_p->position);
    pbtools_encoder_write_uint32(encoder_p, 1, self_p->i);
}

void map_entity_decode_inner(
    struct pbtools_decoder_t *decoder_p,
    struct map_entity_t *self_p)
{
    int wire_type;
    struct pbtools_repeated_info_t repeated_info_position;
    struct pbtools_repeated_info_t repeated_info_rotation;

    pbtools_repeated_info_init(&repeated_info_position, 2);
    pbtools_repeated_info_init(&repeated_info_rotation, 3);

    while (pbtools_decoder_available(decoder_p)) {
        switch (pbtools_decoder_read_tag(decoder_p, &wire_type)) {

        case 1:
            self_p->i = pbtools_decoder_read_uint32(decoder_p, wire_type);
            break;

        case 2:
            pbtools_repeated_info_decode_float(
                &repeated_info_position,
                decoder_p,
                wire_type);
            break;

        case 3:
            pbtools_repeated_info_decode_float(
                &repeated_info_rotation,
                decoder_p,
                wire_type);
            break;

        default:
            pbtools_decoder_skip_field(decoder_p, wire_type);
            break;
        }
    }

    pbtools_decoder_decode_repeated_float(
        decoder_p,
        &repeated_info_position,
        &self_p->position);
    pbtools_decoder_decode_repeated_float(
        decoder_p,
        &repeated_info_rotation,
        &self_p->rotation);
}

int map_entity_position_alloc(
    struct map_entity_t *self_p,
    int length)
{
    return (pbtools_alloc_repeated_float(
                &self_p->base,
                length,
                &self_p->position));
}

int map_entity_rotation_alloc(
    struct map_entity_t *self_p,
    int length)
{
    return (pbtools_alloc_repeated_float(
                &self_p->base,
                length,
                &self_p->rotation));
}

void map_entity_encode_repeated_inner(
    struct pbtools_encoder_t *encoder_p,
    int field_number,
    struct map_entity_repeated_t *repeated_p)
{
    pbtools_encode_repeated_inner(
        encoder_p,
        field_number,
        (struct pbtools_repeated_message_t *)repeated_p,
        sizeof(struct map_entity_t),
        (pbtools_message_encode_inner_t)map_entity_encode_inner);
}

void map_entity_decode_repeated_inner(
    struct pbtools_decoder_t *decoder_p,
    struct pbtools_repeated_info_t *repeated_info_p,
    struct map_entity_repeated_t *repeated_p)
{
    pbtools_decode_repeated_inner(
        decoder_p,
        repeated_info_p,
        (struct pbtools_repeated_message_t *)repeated_p,
        sizeof(struct map_entity_t),
        (pbtools_message_init_t)map_entity_init,
        (pbtools_message_decode_inner_t)map_entity_decode_inner);
}

void map_init(
    struct map_t *self_p,
    struct pbtools_heap_t *heap_p)
{
    self_p->base.heap_p = heap_p;
    self_p->name_p = "";
    pbtools_bytes_init(&self_p->ambient_color);
    pbtools_bytes_init(&self_p->sky_color);
    pbtools_bytes_init(&self_p->ground_color);
    self_p->objects.length = 0;
    self_p->set.length = 0;
    self_p->fix.length = 0;
    self_p->chk.length = 0;
}

void map_encode_inner(
    struct pbtools_encoder_t *encoder_p,
    struct map_t *self_p)
{
    map_entity_encode_repeated_inner(
        encoder_p,
        8,
        &self_p->chk);
    map_entity_encode_repeated_inner(
        encoder_p,
        7,
        &self_p->fix);
    map_entity_encode_repeated_inner(
        encoder_p,
        6,
        &self_p->set);
    pbtools_encoder_write_repeated_string(encoder_p, 5, &self_p->objects);
    pbtools_encoder_write_bytes(encoder_p, 4, &self_p->ground_color);
    pbtools_encoder_write_bytes(encoder_p, 3, &self_p->sky_color);
    pbtools_encoder_write_bytes(encoder_p, 2, &self_p->ambient_color);
    pbtools_encoder_write_string(encoder_p, 1, self_p->name_p);
}

void map_decode_inner(
    struct pbtools_decoder_t *decoder_p,
    struct map_t *self_p)
{
    int wire_type;
    struct pbtools_repeated_info_t repeated_info_objects;
    struct pbtools_repeated_info_t repeated_info_set;
    struct pbtools_repeated_info_t repeated_info_fix;
    struct pbtools_repeated_info_t repeated_info_chk;

    pbtools_repeated_info_init(&repeated_info_objects, 5);
    pbtools_repeated_info_init(&repeated_info_set, 6);
    pbtools_repeated_info_init(&repeated_info_fix, 7);
    pbtools_repeated_info_init(&repeated_info_chk, 8);

    while (pbtools_decoder_available(decoder_p)) {
        switch (pbtools_decoder_read_tag(decoder_p, &wire_type)) {

        case 1:
            pbtools_decoder_read_string(decoder_p, wire_type, &self_p->name_p);
            break;

        case 2:
            pbtools_decoder_read_bytes(decoder_p, wire_type, &self_p->ambient_color);
            break;

        case 3:
            pbtools_decoder_read_bytes(decoder_p, wire_type, &self_p->sky_color);
            break;

        case 4:
            pbtools_decoder_read_bytes(decoder_p, wire_type, &self_p->ground_color);
            break;

        case 5:
            pbtools_repeated_info_decode_string(
                &repeated_info_objects,
                decoder_p,
                wire_type);
            break;

        case 6:
            pbtools_repeated_info_decode(&repeated_info_set,
                                         decoder_p,
                                         wire_type);
            break;

        case 7:
            pbtools_repeated_info_decode(&repeated_info_fix,
                                         decoder_p,
                                         wire_type);
            break;

        case 8:
            pbtools_repeated_info_decode(&repeated_info_chk,
                                         decoder_p,
                                         wire_type);
            break;

        default:
            pbtools_decoder_skip_field(decoder_p, wire_type);
            break;
        }
    }

    pbtools_decoder_decode_repeated_string(
        decoder_p,
        &repeated_info_objects,
        &self_p->objects);
    map_entity_decode_repeated_inner(
        decoder_p,
        &repeated_info_set,
        &self_p->set);
    map_entity_decode_repeated_inner(
        decoder_p,
        &repeated_info_fix,
        &self_p->fix);
    map_entity_decode_repeated_inner(
        decoder_p,
        &repeated_info_chk,
        &self_p->chk);
}

int map_objects_alloc(
    struct map_t *self_p,
    int length)
{
    return (pbtools_alloc_repeated_string(
                &self_p->base,
                length,
                &self_p->objects));
}

int map_set_alloc(
    struct map_t *self_p,
    int length)
{
    return (pbtools_alloc_repeated(
                (struct pbtools_repeated_message_t *)&self_p->set,
                length,
                self_p->base.heap_p,
                sizeof(struct map_entity_t),
                (pbtools_message_init_t)map_entity_init));
}

int map_fix_alloc(
    struct map_t *self_p,
    int length)
{
    return (pbtools_alloc_repeated(
                (struct pbtools_repeated_message_t *)&self_p->fix,
                length,
                self_p->base.heap_p,
                sizeof(struct map_entity_t),
                (pbtools_message_init_t)map_entity_init));
}

int map_chk_alloc(
    struct map_t *self_p,
    int length)
{
    return (pbtools_alloc_repeated(
                (struct pbtools_repeated_message_t *)&self_p->chk,
                length,
                self_p->base.heap_p,
                sizeof(struct map_entity_t),
                (pbtools_message_init_t)map_entity_init));
}

void map_encode_repeated_inner(
    struct pbtools_encoder_t *encoder_p,
    int field_number,
    struct map_repeated_t *repeated_p)
{
    pbtools_encode_repeated_inner(
        encoder_p,
        field_number,
        (struct pbtools_repeated_message_t *)repeated_p,
        sizeof(struct map_t),
        (pbtools_message_encode_inner_t)map_encode_inner);
}

void map_decode_repeated_inner(
    struct pbtools_decoder_t *decoder_p,
    struct pbtools_repeated_info_t *repeated_info_p,
    struct map_repeated_t *repeated_p)
{
    pbtools_decode_repeated_inner(
        decoder_p,
        repeated_info_p,
        (struct pbtools_repeated_message_t *)repeated_p,
        sizeof(struct map_t),
        (pbtools_message_init_t)map_init,
        (pbtools_message_decode_inner_t)map_decode_inner);
}

struct map_t *
map_new(
    void *workspace_p,
    size_t size)
{
    return (pbtools_message_new(
                workspace_p,
                size,
                sizeof(struct map_t),
                (pbtools_message_init_t)map_init));
}

int map_encode(
    struct map_t *self_p,
    uint8_t *encoded_p,
    size_t size)
{
    return (pbtools_message_encode(
                &self_p->base,
                encoded_p,
                size,
                (pbtools_message_encode_inner_t)map_encode_inner));
}

int map_decode(
    struct map_t *self_p,
    const uint8_t *encoded_p,
    size_t size)
{
    return (pbtools_message_decode(
                &self_p->base,
                encoded_p,
                size,
                (pbtools_message_decode_inner_t)map_decode_inner));
}
