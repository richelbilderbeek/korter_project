# korter_project

## Abstract


## Introduction

A plant can only helplessly experience the changes
in its environment and surroundings. 
Like any organism, it has traits to adapt to changes.
Within the species, there will be variation in that trait. 
Variation in traits is important, as it aids the species in surviving future 
selection pressures. 

Plant species interact, for example, they compete for light and soil
nutrients. One of the more recent ideas in the field, is the idea of
nurse and beneficiary species: the nurse species, say a shrub, colonizes
a barren patch of soil, thanks to -for example- a high drought resistance.
A nurse plant modifies (?ecosystem engineer?) its surroundings by,
for example making the soil more moist due to its roots, or providing shade. 
This will carve out a niche where other plants *can* suddenly grow. We
name such a species a beneficiary plant. Brachypodium, a grass, is such a plant
that is commonly observed to take that role.

An open question is whether such interactions between nurse and facilitated 
plants are stabilizing an ecosystem and/or open up avenues for an
ecosystem catatstrophe. One could argue that adding niches due to facilitation
aids in getting a more speciose environment. But one could also reason
the other way around: would the nurse species perish, perhaps the
facilitated species would do as well.

This latter case assumes that a facilitated species would specialize
on being in such a situation. Such a specialization, for example,
a loss in drought resistance, would be detrimental would the nurse
species perish. However, would the facilitated species remain a
generalist, the removal of a nurse species would still assure its
survival. 

It is straightforward to measure if a species becomes more
of a specialist: its genetic variation will decrease.
In this theoretical study, we measure the genetic variation
of an in silico system under a range of parameters.
This helps us predict when the loss of a nurse species
will also cause a loss of the facilitated species,
in which case the conservation of one (nurse) species may
actually be the conservation of two.

## Research question

What is the effect of nurse species on the genetic variation 
of the species they facilitate?

## Hypothesis

If all patches are unfacilitated, all plants'
trait values will evolve to the value with the highest fitness
for unfacilitated plants

If there are unfacilitated and also unfacilitated patches,
we expect an increase in the variation of trait values,
as there are twice as much niches.

## Methods

`korter_project` is a two-dimensional cellular automaton, of which each
cell can be empty, occupied by a nurse plant or occupied by a non-nurse plant.
A non-nurse plant can be facilitated if vertically or horizontally
adjacent to a nurse plant, and is unfacilitated if this is not the case.
The fixed number of nurse plants occupy the same patches throughout the 
simulation [this may be both a strength and a weakness of the experiment,
I don't know yet]. Generations of non-nurse plants are non-overlapping: 
their seeds are put in a random empty square, germinate, 
produce new seeds and then die.

Every generation, a fixed number of seeds are put in random empty squares,
after which the square is occupied and does not accept new seedlings.
After all seeds are planted, these germinate and produce new seeds.
The higher the fitness of a plant, the likelier it will produce
seeds that will pass to the next generation. In this way, the plant
population produces seeds until there are as much seeds as the
number of non-nurse plants.

Fitness is determined by the seed being facilitated or not,
and its trait value. We assume that the fitness of a trait
is a normal distribution based on that trait value. For the
facilitated and unfacilitated plants, we can set different
such normal distributions. Of both fitness (normal) distributions,
we can set a mean, standard deviation and maximum (i.e. the 
fitness achieved at the optimal trait value; the height of
the Gaussian curve).

The genotype of a seed equals its phenotype. In other words,
the trait is assumed to lie on a haploid genome,
with an infinite amount of loci,
each locus contributing equally and additively to the trait's expression.
Every new offspring seed inherits its asexual parent's trait
with a small random mutation, which is normally distributed around zero,
with standard deviation `mu`. If an offspring's trait values goes below zero,
its trait value is set to zero.
The initial population has its traits drawn from a normal distribution
with a given mean and standard deviation.

## Results

[This is just anecdotal evidence]

We never see a generalist facilitated species arise. Trait values
always shift to a unimodel distribution, specializing on either
being facilitated or unfacilitated.

The specialization on the role with highest (global) fitness is not
always achieved, as the trait values do not always converge to that
optimum and specialization takes place on the other role instead.


## Future

Currently, each new seed is put in a random grid cell. This removes
the option for seeds to specialize on being facilitated or not.
One way to resolve this, is to put each new seed only on adjacent grid cells:
we can then expect that seeds adjacent to nurse plants specialize mostly
on that situation, were the unfacilitated plants in big bare patches will
specialize on that situation.  